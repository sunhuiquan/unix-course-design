#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>

#include "inet_stream_sockets.h"
#include "util.h"

#define MAX_BUF 4096
#define MAX_EVENTS 100 // 最好是动态调整
#define SERVICE "echo"

int main(int argc, char *argv[])
{
	int epfd, lfd, cfd, ready, readn;
	struct epoll_event ev;
	struct epoll_event evlist[MAX_EVENTS];
	char buf[MAX_BUF];

	lfd = inetStreamListen(SERVICE, 512, NULL); // 生成监听套接字
	if (lfd == -1)
		logErrExit("inetStreamListen");

	epfd = epoll_create(1); // 该参数已废弃无意义，随便一个正数即可
	if (epfd == -1)
		logErrExit("epoll_create");

	ev.events = EPOLLIN; // 只关注输入，即收到对端的 connect 请求
	ev.data.fd = lfd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev) == -1)
		logErrExit("epoll_ctl");

	while (1)
	{
		ready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
		if (ready == -1)
		{
			if (errno == EINTR)
				continue; // 如果被信号中断则重新开始
			else
				logErrExit("epoll_wait");
		}

		for (int i = 0; i < ready; ++i)
		{
			if (evlist[i].data.fd == lfd) // 监听套接字
			{
				if (evlist[i].events & EPOLLIN)
				{
					cfd = accept(lfd, NULL, NULL);
					if (cfd == -1)
						logErrExit("accept");

					ev.events = EPOLLIN; // 只关注输入，即收到对端的 connect 请求
					ev.data.fd = cfd;
					if (epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev) == -1)
						logErrExit("epoll_ctl");
				}
				else if (evlist[i].events & (EPOLLERR | EPOLLHUP))
					logErrExit("listening socket failed");
			}
			else // 连接套接字
			{
				if (evlist[i].events & EPOLLIN)
				{
					// 注意一定不能循环 read，不然会阻塞卡死
					readn = read(evlist[i].data.fd, buf, MAX_BUF);
					if (readn == -1)
						logErrExit("read");

					if (readn == 0)
					{
						if (close(evlist[i].data.fd) == -1)
							logErrExit("close");
					}
					else if (write(evlist[i].data.fd, buf, readn) != readn)
						logErrExit("write");
				}
				else if (evlist[i].events & (EPOLLHUP | EPOLLERR))
				{
					// 对端关闭，收到EOF
					if (close(evlist[i].data.fd) == -1)
						logErrExit("close");
				}
			}
		}
	}

	exit(EXIT_SUCCESS);
}

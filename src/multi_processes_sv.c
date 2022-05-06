/* 多进程服务器模型 */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

#include "../include/inet_stream_sockets.h"
#include "../include/util.h"

#define SERVICE "echo" // 周知服务名，echo 服务对应端口 7
#define BUF_SIZE 4096

/* SIGCHLD 信号处理函数 */
static void reaper(int sig)
{
	int savedErrno = errno; // 防止 handler 修改 errno

	// 循环 + 非阻塞，因为重复信号可能丢失，所以要这样确保全部回收
	while (waitpid(-1, NULL, WNOHANG) > 0)
		continue;

	errno = savedErrno;
}

/* ECHO 服务功能代码 */
static void handleRequest(int cfd)
{
	char buf[BUF_SIZE];
	ssize_t numRead;

	while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
		if (write(cfd, buf, numRead) != numRead)
		{
			syslog(LOG_ERR, "write (%s)", strerror(errno)); // 错误写入日志
			_exit(EXIT_FAILURE);
		}

	if (numRead == -1)
	{
		syslog(LOG_ERR, "read (%s)", strerror(errno));
		_exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	int lfd, cfd;
	struct sigaction sa;

	// 设置 SIGCHLD 信号处理函数
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = reaper;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		logErrExit("sigaction");

	// 生成监听套接字
	lfd = inetStreamListen(SERVICE, 10, NULL);
	if (lfd == -1)
		logErrExit("inetStreamConnect");

	/* 多进程模型：一个子进程为一个客户的请求提供服务，父进程不断 accept 等待来自
	 * 客户的 connect 请求，生成连接套接字后 fork 让子进程为该客户提供服务，父进程
	 * 循环继续 accept 等待下一个客户的请求。
	 */
	while(1)
	{
		// 建立 TCP 连接，生成连接套接字
		cfd = accept(lfd, NULL, NULL); /* Wait for connection */
		if (cfd == -1)
			logErrExit("accept");

		switch (fork())
		{
		case -1:
			// fork 失败，关闭 cfd 并重新循环等待下一次连接再尝试
			syslog(LOG_ERR, "Can't create child (%s)", strerror(errno));
			close(cfd);
			break;

		case 0:
			close(lfd);
			handleRequest(cfd);
			_exit(EXIT_SUCCESS); // 良好习惯，子进程退出不要刷新 stdio 缓冲区

		default:
			close(cfd); // 父进程关闭连接套接字，让指向的打开文件表项的计数只是子进程的一个
			break;
		}
	}
}

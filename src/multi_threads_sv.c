#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

#include "inet_stream_sockets.h"
#include "util.h"

#define SERVICE "echo" // 周知服务名，echo 服务对应端口 7
#define BUF_SIZE 4096

static void *
threadFunc(void *arg)
{
	int cfd = (int)arg;
	char buf[BUF_SIZE];
	ssize_t numRead;

	while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
		if (write(cfd, buf, numRead) != numRead)
		{
			syslog(LOG_ERR, "write (%s)", strerror(errno)); // 错误写入日志
			return NULL;									// 只结束线程本身
		}

	if (numRead == -1)
	{
		syslog(LOG_ERR, "read (%s)", strerror(errno));
		return NULL;
	}

	return NULL; // 正常读到EOF，说明对端关闭，然后正常结束服务终止
}

int main(int argc, char *argv[])
{
	pthread_attr_t attr;
	int s, lfd, cfd;

	// 初始化线程属性
	s = pthread_attr_init(&attr);
	if (s != 0)
		errExitEN(s, "pthread_attr_init");

	// 设置线程属性创建立即分离
	s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (s != 0)
		errExitEN(s, "pthread_attr_setdetachstate");

	// 生成监听套接字
	lfd = inetStreamListen(SERVICE, 10, NULL);
	if (lfd == -1)
		logErrExit("inetStreamConnect");

	while (1)
	{
		// 建立 TCP 连接，生成连接套接字
		cfd = accept(lfd, NULL, NULL); /* Wait for connection */
		if (cfd == -1)
			logErrExit("accept"); // 服务器上的错误，exit 进程终止，所有线程终止

		// 创建线程
		s = pthread_create(NULL, &attr, threadFunc, (void *)cfd);
		if (s != 0)
			logErrExit("pthread_create");
	}

	// attr 虽然是动态分配的，但一直被使用，而且服务器是无限循环的，所以不需要释放
	exit(EXIT_SUCCESS);
}

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
			return NULL;									// 只结束线程本身，避免终止整个服务器进程
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
	pthread_t dummy_thr; // 无用，只是作为参数
	pthread_attr_t attr;
	int r, lfd, cfd;

	// 初始化线程属性
	r = pthread_attr_init(&attr);
	if (r != 0)
		threadLogErrExit("pthread_attr_init", r);

	// 设置线程属性创建立即分离，使僵尸线程自动被回收
	r = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (r != 0)
		threadLogErrExit("pthread_attr_setdetachstate", r);

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
		r = pthread_create(&dummy_thr, &attr, threadFunc, (void *)cfd);
		if (r != 0)
			threadLogErrExit("pthread_create", r);
	}

	// attr 虽然是动态分配的，但一直被使用，而且服务器是无限循环的，所以不需要释放
	exit(EXIT_SUCCESS);
}

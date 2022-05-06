/* 并发性能测试 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

#include "inet_stream_sockets.h"
#include "util.h"

#define BUF_SIZE 128

const char *MSG = "echo";
const int MSG_LEN = 4;

static void *request(void *arg)
{
	int sfd, epfd;
	ssize_t numRead;
	char buf[BUF_SIZE];

	// 向服务器发送 TCP 请求，并生成一个流式套接字
	sfd = inetStreamConnect((char *)arg, "echo");
	if (sfd == -1)
	{
		printf("In request thread inetStreamConnect failed: %s\n", strerror(errno));
		return NULL;
	}

	// 下面代码为了简化，没有考虑部分读/写等情况，是不安全的代码
	// 但实际上已经足够用了，因为服务器的功能是 echo，而我们客户端
	// 又是 write 一次 read 一次，足够可靠了。
	for (int i = 0; i < 5; ++i)
	{
		if (write(sfd, MSG, MSG_LEN) != MSG_LEN)
		{
			printf("In request thread write failed: %s\n", strerror(errno));
			return NULL;
		}

		numRead = read(sfd, buf, BUF_SIZE);
		if (numRead != MSG_LEN || strncmp(MSG, buf, MSG_LEN) != 0) // 出错/部分读
		{
			printf("In request thread read failed: %s\n", strerror(errno));
			return NULL;
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int numRequest, r;
	pthread_t *threads;
	double sec;
	struct timeval start, end;

	if (gettimeofday(&start, NULL) == -1)
		errExit("gettimeofday");

	// 检查命令行参数
	if ((argc != 2 && argc != 3) || strcmp(argv[1], "--help") == 0)
		usageErrExit(argv[0], "<hostname> [request number]");
	if (argc == 3)
		numRequest = atoi(argv[2]);
	else
		numRequest = 300;

	threads = (pthread_t *)malloc(numRequest * sizeof(pthread_t));
	memset(threads, 0, numRequest * sizeof(pthread_t));

	for (int i = 0; i < numRequest; ++i)
	{
		r = pthread_create(&threads[i], NULL, request, (void *)argv[1]);
		if (r != 0)
			threadErrExit("pthread_create", r);
	}

	for (int i = 0; i < numRequest; ++i)
	{
		r = pthread_join(threads[i], NULL);
		if (r != 0)
			threadErrExit("pthread_join", r);
	}

	if (gettimeofday(&end, NULL) == -1)
		errExit("gettimeofday");
	;
	free(threads);

	sec = end.tv_sec - start.tv_sec + (double)(end.tv_usec - start.tv_usec) / 1000000;
	printf("%d threads requests cost: %.4lf seconds.\n", numRequest, sec);

	return 0;
}

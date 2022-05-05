/* 单客户请求 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "inet_stream_sockets.h"
#include "util.h"

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];

	// 检查命令行参数
	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErrExit(argv[0], "<hostname>");

	// 向服务器发送 TCP 请求，并生成一个流式套接字
	sfd = inetStreamConnect(argv[1], "echo");
	if (sfd == -1)
		errExit("inetStreamConnect");

	switch (fork())
	{
	case -1:
		errExit("fork");

	case 0:
		// 子进程接受服务器发来的相应并输出到 STDOUT 上
		for (;;)
		{
			numRead = read(sfd, buf, BUF_SIZE - 1);
			if (numRead <= 0) // 服务端关闭读取到 EOF 或者出错
				break;
			buf[numRead] = '\0'; // read 的 BUF_SIZE-1 保证了不会越界
			printf("%s", buf);
		}
		exit(EXIT_SUCCESS); // 此时需要刷新 stdio，所以子进程没用 _exit()，而且 fork() 前的 stdio 本就为空不影响

	default:
		// 父进程从标准输入读取信息然后发送给服务器
		for (;;)
		{
			numRead = read(STDIN_FILENO, buf, BUF_SIZE);
			if (numRead <= 0)
				break;
			if (write(sfd, buf, numRead) != numRead)
				errExit("write");
		}

		// 关闭客户端的写端（因为信息没收完子进程还要接着读），这样服务端就会在发送完
		// 所有信息后得知客户请求结束，然后服务端的子进程终止关闭服务端的连接套接字，
		// 之后客户端的子进程会读到 EOF 然后终止。
		if (shutdown(sfd, SHUT_WR) == -1)
			errExit("shutdown");
		exit(EXIT_SUCCESS);
	}
}

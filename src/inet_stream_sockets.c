#include "inet_stream_sockets.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*	生成流式套接字，然后向服务端 host 和 service 对应的地址发起 connect 请求，
	如果成功完成 TCP 连接则返回对应套接字 fd，否则返回 -1。

	参数：
		host：		主机名 / 域名 / IP地址(点分十进制)
		service:	服务吗 / 端口号
*/
int inetStreamConnect(const char *host, const char *service)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;	 // IPv4 或 IPv6
	hints.ai_socktype = SOCK_STREAM; // 流式套接字

	s = getaddrinfo(host, service, &hints, &result);
	if (s != 0)
	{
		errno = ENOSYS;
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;

		close(sfd);
	}

	freeaddrinfo(result);

	return (rp == NULL) ? -1 : sfd;
}

/*  创建流式套接字，绑定到通配地址以及对应端口，然后使用 listen() 变成
	监听套接字。成功则返回该监听套接字的 fd，否则返回 -1。

	参数：
		service:	服务吗 / 端口号
		type:		套接字类型
		addrlen：	返回地址长度(非NULL)
*/
// to do
int inetStreamListen(const char *service, int backlog, socklen_t *addrlen)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, optval, s;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_socktype = SOCK_STREAM; // 流式套接字
	hints.ai_family = AF_UNSPEC;	 // IPv4 或 IPv6
	hints.ai_flags = AI_PASSIVE;	 // 使用通配符地址，用于服务端绑定监听套接字

	s = getaddrinfo(NULL, service, &hints, &result);
	if (s != 0)
		return -1;

	optval = 1;
	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		// 开启 SO_REUSEADDR 选项，让 TIME_WAIT 不必等待 2MSL
		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		{
			close(sfd);
			freeaddrinfo(result);
			return -1;
		}

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sfd);
	}

	if (rp != NULL && listen(sfd, backlog) == -1)
	{
		freeaddrinfo(result);
		return -1;
	}

	if (rp != NULL && addrlen != NULL)
		*addrlen = rp->ai_addrlen;

	freeaddrinfo(result);

	return (rp == NULL) ? -1 : sfd;
}

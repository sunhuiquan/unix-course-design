#ifndef INET_STREAM_SOCKETS_H
#define INET_STREAM_SOCKETS_H

#include <sys/socket.h>
#include <netdb.h>

int inetStreamConnect(const char *host, const char *service);

int inetStreamListen(const char *service, int backlog, socklen_t *addrlen);

#endif

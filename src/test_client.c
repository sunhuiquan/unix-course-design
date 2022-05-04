#include "inet_sockets.h"
#include "util.h"

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErrExit(argv[0], "<hostname>");

	sfd = inetConnect(argv[1], "echo", SOCK_STREAM);
	if (sfd == -1)
		errExit("inetConnect");

	switch (fork())
	{
	case -1:
		errExit("fork");

	case 0:
		for (;;)
		{
			numRead = read(sfd, buf, BUF_SIZE);
			if (numRead <= 0)
				break;
			printf("%.*s", (int)numRead, buf);
		}
		exit(EXIT_SUCCESS);

	default:
		for (;;)
		{
			numRead = read(STDIN_FILENO, buf, BUF_SIZE);
			if (numRead <= 0)
				break;
			if (write(sfd, buf, numRead) != numRead)
				errExit("write");
		}

		if (shutdown(sfd, SHUT_WR) == -1)
			errExit("shutdown");
		exit(EXIT_SUCCESS);
	}
}

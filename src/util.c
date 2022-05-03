#include "util.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void errExit(const char *msg)
{
	printf("%s failed: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

void usageErrExit(const char *name, const char *msg)
{
	printf("Usage: %s %s\n", name, msg);
	exit(EXIT_FAILURE);
}

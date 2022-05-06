#include "util.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

/* 输出错误并终止进程 */
void errExit(const char *msg)
{
	printf("%s failed: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

/* 输出错误并终止进程，处理 pthread API 错误 */
void threadErrExit(const char *msg, int err)
{
	printf("%s failed: %s\n", msg, strerror(err));
	exit(EXIT_FAILURE);
}

/* 参数错误，输出正确的命令使用格式然后终止进程 */
void usageErrExit(const char *name, const char *msg)
{
	printf("Usage: %s %s\n", name, msg);
	exit(EXIT_FAILURE);
}

/* 将错误写入日志并终止进程 */
void logErrExit(const char *msg)
{
	syslog(LOG_ERR, "%s (%s)", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

/* 将错误写入日志并终止进程，处理 pthread API 错误 */
void threadLogErrExit(const char *msg, int err)
{
	syslog(LOG_ERR, "%s (%s)", msg, strerror(err));
	exit(EXIT_FAILURE);
}

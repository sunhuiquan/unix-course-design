#ifndef UTIL_H
#define UTIL_H

void errExit(const char *msg);

void threadErrExit(const char *msg, int err);

void usageErrExit(const char *name, const char *msg);

void logErrExit(const char *msg);

void threadLogErrExit(const char *msg, int err);

#endif

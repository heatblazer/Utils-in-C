#ifndef LOGFILES_H
#define LOGFILES_H
#define LOGNORM     "/home/ilian/lognorm.txt"
#define LOGERR      "/home/ilian/logerr.txt"
#define LOGOTHER    "/home/ilian/logother.txt"
#define NORMAL 0
#define OTHER 1
#define ERRORR 2

#include <stdio.h>


FILE* LOG_getLogNorm();
FILE* LOG_getLogErr();
FILE* LOG_getLogOther();

void LOG_setNorm(const char*);
void LOG_setErr(const char*);
void LOG_setOther(const char*);

const char* LOG_getLogName(int);

int openAll();
int closeAll();
#endif // LOGFILES_H

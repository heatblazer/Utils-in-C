#include "LOGFILES.h"
#include <stdio.h>
#define DBG1

static const char* logNormal;
static const char* logError;
static const char* logOther;


static FILE* logfileNormal;
static FILE* logfileErr ;
static FILE* logfileOther ;

FILE* LOG_getLogNorm() { return logfileNormal; }
FILE* LOG_getLogErr() { return logfileErr; }
FILE* LOG_getLogOther() { return logfileOther; }
#ifdef DBG1
int openAll() {
    logfileNormal = fopen(logNormal, "a+");
    logfileErr = fopen(logError, "a+");
    logfileOther = fopen(logOther, "a+");
    if ( logfileNormal && logfileErr && logfileOther ) {
        return 0;
    } else {
        return -1;
    }
}
#else
int openAll() {
    logfileNormal = fopen(LOGNORM, "a+");
    logfileErr = fopen(LOGERR, "a+");
    logfileOther = fopen(LOGOTHER, "a+");
    if ( logfileNormal && logfileErr && logfileOther ) {
        return 0;
    } else {
        return -1;
    }
}
#endif
int closeAll() {

    if (fclose(logfileNormal) &&
            fclose(logfileErr) &&
            fclose(logfileOther)) {
        return 0;
    } else {
        return -1;
    }
}


void LOG_setNorm(const char *ln)
{
   logNormal = ln;
}


void LOG_setErr(const char *le)
{
    logError = le;
}


void LOG_setOther(const char *lo)
{
    logOther = lo;
}



const char *LOG_getLogName(int i)
{

    if ( i == NORMAL) {
        return logNormal;
    } else if ( i==OTHER) {
        return logOther;
    } else if ( i == ERRORR) {
        return logError;
    } else {
        return 0x00;
    }
}

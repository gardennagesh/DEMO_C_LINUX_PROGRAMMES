/************************************File4 abc.C *********************************************************************
This file(one module) :  abc.c
Pls look into main.c for usage.
**********************************************************************************************************************/


#include<stdio.h>
#include"logmsg.h"

extern int ABC_log_level;
extern int log_module;

void ABC_func (void) {

        log_module=ABC_log_level;

        logmsg( DEBUG, "debug msg  enabled in ABCmod" );
        logmsg( INFO,  "info  msg  enabled in ABCmod"  );
        logmsg( ERROR, "error msg  enabled in ABCmod" );
        logmsg( WARN,  "warn  msg  enabled in ABCmod" );
}




/***********************************File5  xyz.C *********************************************************************
This file(another module) :  xyz.c
Pls look into main.c for usage.
**********************************************************************************************************************/

#include<stdio.h>
#include"logmsg.h"

extern int XYZ_log_level;
extern int log_module;

void XYZ_func (void) {

        log_module = XYZ_log_level;

        logmsg( DEBUG, "debug msg  enabled in XYZmod" );
        logmsg( INFO,  "info  msg  enabled in XYZmod"  );
        logmsg( ERROR, "error msg  enabled in XYZmod" );
        logmsg( WARN,  "warn  msg  enabled in XYZmod" );
}


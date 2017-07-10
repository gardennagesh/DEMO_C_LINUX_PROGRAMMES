/**************************************File3: logmsg.c****************************************************************
This file(logger module) :  logmsg.c
Pls look into main.c for usage.
**********************************************************************************************************************/


#include <stdio.h>
#include "logmsg.h"

int log_module;
int ABC_log_level;
int XYZ_log_level;

void logmsg(int ltype, char *msg) {

        if ((log_module & INFO) &&  (ltype == INFO ))  {
                printf ("%s\n", msg);
        }
        if ((log_module & WARN) &&  (ltype == WARN))  {
                printf ("%s\n", msg);
        }
        if ((log_module & ERROR) && (ltype == ERROR))  {
                printf ("%s\n", msg);
        }
        if ((log_module & DEBUG) && (ltype == DEBUG))  {
                printf ("%s\n", msg);
        }

}


/************************************File2: main.c ******************************************************************
 Programmer              : Nagesh Nanjundachari 
 This File (main module) : main.c 
 Header and modules      : 1)logmsg.h  2)main.c  3)logmsg.c    4)abc.c   5)xyz.c  
 This programme is just to demonstrate how dynamic-logger-level can be implemented  
 This programme is NOT multi-Thread-safe. logmsg function is not thread safe   
 USAGE: Compile files in a temp_dir cc -o dylogs main.c abc.c xyz.c logmsg.c 
 Run "./dylogs" executable.
 You can observe log_levels of abc.c and xyz.c changes based upon ODD or EVEN value of random-val.
*********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "logmsg.h"

extern int ABC_log_level;
extern int XYZ_log_level;

void get_module_log_settings (int i) {
long val;


/** IPC or Sockets perfectly replace the random-call for User-control from another process. **/
/** For demo purpose, below dynamically change loglevel based on random val is EVEN or ODD. **/
        val = random();
        if (!(val % 2)) {
                printf ("\nRandom value is even=%li\n",val);
                printf ("\nBelow log levels set in EVEN clause\n");
                printf ("-----------------------------------\n");
                ABC_log_level = ( INFO  | DEBUG );
                XYZ_log_level = ( ERROR | WARN  );
        }
        else {
                printf ("\nRandom value is odd=%li\n",val);
                printf ("\nBelow log levels set in ODD clause\n");
                printf ("-----------------------------------\n");
                ABC_log_level = ( ERROR | WARN  );
                XYZ_log_level = ( INFO  | DEBUG );
        }
}


int main( ) {

	printf ("\n\nPlease wait for 6-seconds. Log-level changes based on random-value\n");


        if (!fork()) {
                while (1) {
                        sleep (1);
                        kill (getppid(), SIGUSR1);
                        sleep (5);
                }
        }
        else {
                signal (SIGUSR1, get_module_log_settings);
                while (1) {
                        ABC_func();
                        sleep (10);
                        XYZ_func();
                }
        }
	return 1;
}



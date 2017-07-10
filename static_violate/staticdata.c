/* This is staticdata.c
 * Module : staticdata.c
 * Static variable stat_val, function  stat_func are bound to file scope within staticdata.c.
 * Eventhough these varaible or function can be accessed out side from violate.c.
 */

#include<stdio.h>

void  * func_ret (int);
static void stat_func (char * );
static int stat_val=9999;

static void stat_func (char * str) {
        printf ("%s\n", str);
}

void  * func_ret(int argc) {
        if (argc%2) return stat_func;
        else return &stat_val;
}

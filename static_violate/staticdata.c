/* This is staticdata.c
 * Module : staticdata.c
 * Static variable stat_val, function  stat_func are bound to file scope within staticdata.c .
 * This varaible or function can be accessed out side of this file and from violate.c . 
 * That is by returning address of variables, via function returning void pointer.
 * func_ret  returns address of stat_val if ODD cmd-line argument passed else returns address of stat_func.
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

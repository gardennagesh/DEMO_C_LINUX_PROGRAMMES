/*
 * FILE : pfarray.c
 * Programmer: Nagesh Nanjundachari  at  garden.nagesh@gmail.com
 * Below lines of code to demonstrate use of pointers with function. Pass ODD or EVEN number of cmd line arguments.
 * func_abc and func_xyz are functions which accept "pointer to char" and return "address of any data type".
 * func_pqr  is  the function returns address of functions which are having similar prototype as func_abc.
 * pf_array  is  array of  pointers to functions of prototype similar to func_abc.
 * PFVAR is a pointer-to-function user-defined data-type.
 *
 * USAGE: Compile run as  ./a.out  OR  ./a.out hi
 */


#include<stdio.h>
#include<string.h>
#include<malloc.h>

void * func_abc (char *);
void * func_xyz (char *);
void * (*func_pqr (int))(char *);
void * (*pf_array[3])(char *) = { func_abc, func_xyz, NULL };
typedef void* (*PFVAR)(char *);


/* This is abc function calls printf */
void * func_abc (char * ptr_str) {

        printf ("\n\n%s  Inside func_ABC  abc function\n\n", ptr_str);
}


/* This is xyz function calls printf */
void * func_xyz (char * ptr_str) {

        printf ("\n\n%s  Inside func_XYZ  xyz function \n\n", ptr_str);
}


/* This function returns pointer to function  based upon number(ODD or EVEN) of cmd-line-args passed.*/
void * (*func_pqr (int argc))(char *) {
        
       return  pf_array[argc%2];

}


/* This MAIN function  which calls func_pqr with number of cmd-line-args */
int main (int argc, char * av[])  {
        
PFVAR temp_pf;

        temp_pf = func_pqr(argc);
        
        temp_pf ("I am Entering");
}


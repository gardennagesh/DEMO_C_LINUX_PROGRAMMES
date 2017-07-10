/* File: violate.c
 * Module : violate.c
 * Programmer       : Nagesh Nanjundachari  Email:  garden.nagesh@gmail.com
 * Purpose: Voilate static keyword purpose.
 * Static variable, functions are bound to file scope. 
 * Such varaible or functions can be accessed out side the file of residence.
 * Compile :  cc  violate.c  staticdata.c
 * USAGE_type_1:  ./a.out 11
 * USAGE_type_2:  ./a.out 11 22
 *
 * OUTPUT: If cmd line arguments are EVEN in number then prints "Hello World".
 * OUTPUT: If cmd line arguments are ODD  in number then prints "9999".
 *          
 */



#include<stdio.h>

void  * func_ret(int argc);

int main (int argc, char * argv[]) {
void (*pf)(char *);

        if (argc%2) {
                pf = (void (*)(char *))func_ret(argc);
                pf("Hello World");
        }

        else {
                printf ("%d\n", *(int *)func_ret(argc));
        }
}



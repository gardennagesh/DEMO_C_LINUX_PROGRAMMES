#include<stdio.h>
void recursive_strrev (char *p);

main () {

char ar1[10] = {"NAGESH"};
char ar2[10] = {"ESREVER"};

printf ("BEFORE str_rev called strings are %s %s\n", ar1, ar2);
recursive_strrev (ar1);
recursive_strrev (ar2);
printf ("AFTER str_rev called strings are %s %s\n", ar1, ar2);

}

void recursive_strrev (char *p) {

static int  len = 0;
static char *q;
static int i=0;
char ch;

if (!len) q = p;

if (*p != 0) {
       ch = *p;
        len++;
        p++;
        recursive_strrev(p);
  *(q+i) = ch;
   i++;
}
if(len == i) { i=0; len=0;  return;}
}
~                                  

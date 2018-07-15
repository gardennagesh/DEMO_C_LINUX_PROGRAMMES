/* Prgrammer : Nagesh Nanjundachari */
/* Task:  Simple programme to demo double pointer usage */

#include<stdio.h>
void single_pointer(char *p, char *q);
void double_pointer (char **p, char **q);

main () {

char *p  = "SPIRIT_MOVIE";

char *q  = "BRYAN_ADAMS";

single_pointer (p, q);
printf ("P points to %s  and Q points to %s\n\n", p, q);

double_pointer (&p, &q);
printf ("P points to %s  and Q points to %s\n\n", p, q);

}

void single_pointer(char *p, char *q) {

char * temp;

  temp = p;
  p = q;
  q = temp;
}

void double_pointer (char **p, char **q) {

char *temp;

  temp = *p;
  *p = *q;
  *q = temp;
}

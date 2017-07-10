/********************************************************************
Programmer :  Nagesh Nanjundachari
Description:  Beauty of pointer demonstration pointing to 2D-ARRAY.
*********************************************************************/
#include<stdio.h>

#define BEFORE_ARRAY_NUMBER    88
#define AFTER_ARRAY_NUMBER     99

/* 2x5=10 elements in 2D array */
/* Do not change below declaration order */

int priv_element = BEFORE_ARRAY_NUMBER;
int array[2][5]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int next_element = AFTER_ARRAY_NUMBER;

/* Below variable name is self explanatory */
int *ptr_to_first_element   = &array[0][0];
int (*ptr_to_1d_arry)[5]    = &array[0];
int (*ptr_to_2d_arry)[2][5] = &array;

int main (int argc, char *argv[])
{

  printf ("Print first num of first array of 2-Dim array: %d\n",
	  *ptr_to_first_element);

  ptr_to_first_element += 5;

  printf ("Print first num of second array of 2-Dim array: %d\n",
	  *ptr_to_first_element);

  printf ("Print first num of first array of 2-Dim array: %d\n",
	  (*ptr_to_1d_arry)[0]);

  ptr_to_1d_arry++;

  printf ("Print first num of second array of 2-Dim array: %d\n",
	  (*ptr_to_1d_arry)[0]);

  printf ("Print first num of first array of 2-Dim array: %d\n",
	  (*ptr_to_2d_arry)[0][0]);

  ptr_to_2d_arry++;

  printf
    ("Now you increased to point end of 2d-array space. So next to it is next_element on data-segment: %d\n",
     (*ptr_to_2d_arry)[0][0]);

}

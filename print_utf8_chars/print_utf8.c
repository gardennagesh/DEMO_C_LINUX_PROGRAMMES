/**********************************************************************
Developer: Nagesh Nanjundachari
Task:      Self assignment. Understand UTF-8 6 byte format and write C programme without supported HEADER-FILES.
Code:      Without UTF-8 header files, macros, Print uft-8 chars from hex start point untill length.
Setup:     Make sure your Linux ENVIORNMENT has UTF-8 enabled.
Example:   Prints Misc symbols for hex start 0xE29880.
Usage:     Start point can be changed at Macro: START_SYMBOLS.  Then Compile and Run.
BUGS:      Tested for few languages and Misc sybols.  Need to fix bugs.
***********************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/**************************************** 
* START_SYMBOLS MACRO CAN BE INITIALIZED FOR ANY OF BELOW.
* Start Misc Symbols     : 0xE29880	
* Start DevaNagari       : 0xE0A480	
* Start Hiragana Japan   : 0xE38080	
* Start Playing Cards    : 0xF09F82A0
* HEX Chart Reference    :  http://www.utf8-chartable.de/
********************************************/

#define START_SYMBOLS 0xE29880

/* UTF-8 : BYTE_BITS*/

/* B0_BYTE : 0XXXXXXX : Zero iterationn  */

/* COMMON_BYTE : 10XXXXXX :  */

/* B2_BYTE : 110XXXXX : From this, 2 bytes are part of non_ascii. So p+2*/

/* B3_BYTE : 1110XXXX : From this, 3 bytes are part of non-ascii. So, p+3*/

/* B4_BYTE : 11110XXX : So, p+4 */

/* B5_BYTE : 111110XX */

/* B6_BYTE : 1111110X */

#define B0_BYTE 0x00

#define B1_BYTE 0x80

#define B2_BYTE 0xC0

#define B3_BYTE 0xE0

#define B4_BYTE 0xF0

#define B5_BYTE 0xF8

#define B6_BYTE 0xFC

#define B7_BYTE 0xFE


#define MAX_UTF8_BYTES 6

void bytes_arrange (long long *phex_val);
void func_find_utf8 (char *ptr_to_str);
void print_non_ascii (int bytes, char *pbyte);

int
main (int argc, char *av[])
{

  long long hex_val = START_SYMBOLS;
  long long temp_hex = 0;
  int until = 0;

  if (argc != 2)
    {
      fprintf (stderr, "Run as: ./a.out how_many\n");
      fprintf (stderr, "Example1: ./a.out 25\n");
      fprintf (stderr, "Example2: ./a.out 50\n");
      exit (1);
    }

  until = atoi (av[1]);
  while (until--)
    {

      temp_hex = hex_val;
      bytes_arrange (&hex_val);
      func_find_utf8 ((char *) &hex_val);
      hex_val = temp_hex;
	  /* Below line is a bug , will be fixed */
      ++hex_val;
    }

  return 0;

}

void
func_find_utf8 (char *ptr_to_hex_val)
{


  char *pbyte;

  pbyte = ptr_to_hex_val;

  if ((*pbyte & B1_BYTE) == B0_BYTE)
    {
      return;

    }

  else
    {

      if ((*pbyte & B7_BYTE) == B6_BYTE)
	{
	  print_non_ascii (6, pbyte);

	  return;

	}

      if ((*pbyte & B6_BYTE) == B5_BYTE)
	{

	  print_non_ascii (5, pbyte);

	  return;

	}

      if ((*pbyte & B5_BYTE) == B4_BYTE)
	{

	  print_non_ascii (4, pbyte);

	  return;

	}

      if ((*pbyte & B4_BYTE) == B3_BYTE)
	{

	  print_non_ascii (3, pbyte);

	  return;

	}

      if ((*pbyte & B3_BYTE) == B2_BYTE)
	{

	  print_non_ascii (2, pbyte);

	  return;

	}

    }

}



void
bytes_arrange (long long *phex_val)
{

  int i = 0;
  long long temp_byte;
  char *byte, *hex_val;

  byte = (char *) &temp_byte;
  hex_val = (char *) phex_val;

  if (hex_val[5])
    *(byte + i) = hex_val[5], i++;
  if (hex_val[4])
    *(byte + i) = hex_val[4], i++;
  if (hex_val[3])
    *(byte + i) = hex_val[3], i++;
  if (hex_val[2])
    *(byte + i) = hex_val[2], i++;
  if (hex_val[1])
    *(byte + i) = hex_val[1], i++;
  if (hex_val[0])
    *(byte + i) = hex_val[0], i++;

  memcpy (hex_val, byte, 6);
}


void
print_non_ascii (int bytes, char *pbyte)
{

  int i;

  i = 0;

  while (i < bytes)
    {
      printf ("%c", *(pbyte + i));
      i++;
    }

  printf ("\n");

  fflush (stdout);

}

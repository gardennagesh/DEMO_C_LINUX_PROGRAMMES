/**********************************************************************
Developer: Nagesh Nanjundachari
Email:     garden.nagesh@gmail.com
Task:      It was a coding challenge fired to me. 
Challenge: Read input strings and print only uft-8 chars from string.
Setup:     Make sure your Linux ENVIORNMENT has UTF-8 enabled.
Example:   Hello_123, chess_♕♖_symbols, Pound_£_Symbol, Euro_€_Symbol.
***********************************************************************/


#include<stdio.h>
#include<string.h>

/* UTF-8 : BYTE_BITS*/

/* B0_BYTE : 0XXXXXXX */

/* B1_BYTE : 10XXXXXX */

/* B2_BYTE : 110XXXXX */

/* B3_BYTE : 1110XXXX */

/* B4_BYTE : 11110XXX */

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

/* Please tune this as per number of lines input */

#define MAX_UTF8_STR 10

/* 600 is used because 6byteX100chars */

#define MAX_UTF8_CHR 600

void func_find_utf8 (char *ptr_to_str);

void print_non_ascii (int bytes, char *pbyte);

char strbuf[MAX_UTF8_STR][MAX_UTF8_CHR];

int
main (int ac, char *av[])
{

  int i = 0;

  char no_newln_str[MAX_UTF8_CHR];

  i = 0;

  printf ("\n\nEnter strings with OR without utf-8 chars OR Q/q to exit\n\n");
  printf ("Example: like helloworld OR Chess Symbols or SterlingPound as part of string\n");

  while (i < MAX_UTF8_STR)
    {

      fgets (strbuf[i], MAX_UTF8_CHR, stdin);

      if (!strlen (strbuf[i]))
	break;

      if ((strbuf[i][0] == 'Q') || (strbuf[i][0] == 'q'))
	break;

      strcpy (no_newln_str, strbuf[i]);

      no_newln_str[strlen (no_newln_str) - 1] = 0;

      func_find_utf8 (no_newln_str);

      ++i;

    }

  return 1;

}

void
func_find_utf8 (char *ptr_to_str)
{

  int found_non_ascii;

  char *pbyte;

  pbyte = ptr_to_str;

  found_non_ascii = 0;

  while (*pbyte)
    {

      if ((*pbyte & B1_BYTE) == B0_BYTE)
	{

	  pbyte++;

	  continue;

	}

      else
	{

	  found_non_ascii = 1;

	  if ((*pbyte & B7_BYTE) == B6_BYTE)
	    {

	      print_non_ascii (6, pbyte);

	      pbyte += 6;

	      continue;

	    }

	  if ((*pbyte & B6_BYTE) == B5_BYTE)
	    {

	      print_non_ascii (5, pbyte);

	      pbyte += 5;

	      continue;

	    }

	  if ((*pbyte & B5_BYTE) == B4_BYTE)
	    {

	      print_non_ascii (4, pbyte);

	      pbyte += 4;

	      continue;

	    }

	  if ((*pbyte & B4_BYTE) == B3_BYTE)
	    {

	      print_non_ascii (3, pbyte);

	      pbyte += 3;

	      continue;

	    }

	  if ((*pbyte & B3_BYTE) == B2_BYTE)
	    {

	      print_non_ascii (2, pbyte);

	      pbyte += 2;

	      continue;

	    }

	}

    }

  if (found_non_ascii)
    printf (" These are Non Ascci chars\n");

}

void
print_non_ascii (int bytes, char *pbyte)
{

  char store[6];

  int i;

  memset (store, 0, 6);

  memcpy (store, pbyte, bytes);

  i = 0;

  while (i < bytes)
    printf ("%c", store[i++]);

  printf ("%c", ' ');

  fflush (stdout);

}

/*********************************************************************
Developer: Nagesh Nanjundachari
Email: garden.nagesh@gmail.com
File: notify_me.c
This programme sends future time and event-message to task_server.

For example_1: if you send  "COFFEE_BREAK  00-10-15" . 
You get same message after 10-minutes 15-seconds from now, current_time.

For example_2: if you send  "MEETING_WITH_NAGESH  10-00-15" . 
You get same message after 10-hour 15-minutes from now, current_time.
**********************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>

#define DATA_LEN   100
char tx_data[DATA_LEN];

void
print_usage ()
{
  fprintf (stderr, "WRONG FORMAT DATA ENTERED.\n");
  fprintf (stderr, "Usage:   ./notify_me  alaram_name  HH-MM-SS\n\n");
  fprintf (stderr, "Example: ./notify_me  meeting_1    00-00-09\n");
  fprintf (stderr, "Example: ./notify_me  coffe_brk    00-00-12\n");
  fprintf (stderr, "Example: ./notify_me  meeting_3    00-01-12\n");
  fprintf (stderr, "Example: ./notify_me  food_brek    01-05-00\n");
}

long
make_secs (char *alaram_input)
{

  int hours = -11, minutes = -11, seconds = -11;
  char *tmp = NULL;
/*
  hours = atoi (strtok (alaram_input, "-"));
  minutes = atoi (strtok (NULL, "-"));
  seconds = atoi (strtok (NULL, "-"));
*/

  tmp = strtok (alaram_input, "-");
  if (tmp != NULL)
    {
      hours = atoi (tmp);
      tmp = NULL;
      tmp = strtok (NULL, "-");
      if (tmp != NULL)
	{

	  minutes = atoi (tmp);
	  tmp = NULL;
	  tmp = strtok (NULL, "-");
	  if (tmp != NULL)
	    {
	      seconds = atoi (tmp);
	    }

	}
    }

  if ((hours >= 0) && (minutes >= 0) && (seconds >= 1))
    {
      return (hours * 60 * 60) + (minutes * 60) + seconds;
    }
  else
    {
      print_usage ();
      exit (0);
    }
}

int
main (int argc, char *argv[])
{

  int shm_id, total_secs;
  void *shm_space = NULL;

  if (argc != 3)
    {
      //fprintf (stderr, "I am bit lazy to code format input check for HH-MM-SS\n\n");
      print_usage ();
      exit (1);
    }
  printf ("\nYOU notfied after this much HOURS-MINUTES-SECONDS from NOW\n");
  system ("date");

  shm_id = shm_open ("/SHM_NNN", O_RDWR, 00777);
  if (shm_id < 0)
    perror ("shm_open");
  ftruncate (shm_id, DATA_LEN);
  shm_space =
    mmap (NULL, sizeof (DATA_LEN), PROT_READ | PROT_WRITE, MAP_SHARED,
	  shm_id, 0);
  total_secs = make_secs (argv[2]);
  tx_data[0] = '#';
  sprintf (tx_data + 1, "%d%c%s", total_secs, '#', argv[1]);
  fprintf (stdout,
	   "\n\nYou will be notified by xclok or message name %s after %d seconds from now\n\n",
	   argv[1], total_secs);
  strcpy ((char *) shm_space, tx_data);
}

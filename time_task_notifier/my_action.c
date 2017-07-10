/*********************************************************************
Developer: NAgesh Nanjundachari
Email: garden.nagesh@gmail.com
File: my_action.c
Desc: This programme executed by task_server . 
This programme execs "xclock" and messages sent by notifier programme.
Note: In place of xlcok, you can have your own programme which may be mp3 player.
*********************************************************************/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define MSG_LEN 100

int     rx_secs;
int     sound_or_gui_played;
char    rx_message[MSG_LEN];
timer_t timer_id;

void count_down (void)
{

  struct itimerspec time_detail;

  memset (&time_detail, 0, sizeof(struct itimerspec));

  time_detail.it_value.tv_sec = rx_secs;

  timer_create (CLOCK_REALTIME, NULL, &timer_id);

  timer_settime (timer_id, 0, &time_detail, NULL);

}


void play_alaram(int sig)
{
  int i=10;
  while (i--) printf ("You  have alaram messgae = %s........  \n", rx_message);
  fflush (stdout);
  //Nice to play music exec__mpg123();
  execlp ("/usr/bin/xclock", "xclock", NULL);
  // below flag is dummy_working. exec overlays this process.
  // below fla is usefull only fork+exec was done.
  sound_or_gui_played=1;

}

int
main (int ac, char **av)
{
  if (ac != 3) {
        fprintf (stderr, "less args passed\n");
        fprintf (stderr, "Usage: ./alaram  message  secs\n");
        fprintf (stderr, "Example: ./alaram  meeting_1  10\n");
        exit (1);
  }
  (void) signal (SIGALRM, play_alaram);
  strcpy (rx_message, av[1]);
  rx_secs = atoi(av[2]);
  count_down ();
  while (!sound_or_gui_played);
  exit(0);
}

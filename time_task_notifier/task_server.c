/*********************************************************************
Developer: Nagesh Nanjundachari
Email: garden.nagesh@gmail.com
File: task_server.c
This programme runs in the back ground. This receives messages and time from notify_me.
And then executes my_action.
**************************************************************************/


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
char rx_data[DATA_LEN];
char rx_secs[DATA_LEN];
char rx_alname[DATA_LEN];

void get_secs_alname (char *rx_data) {
int i=0;
        while (*++rx_data != '#') rx_secs[i++] = *rx_data;
        strcpy (rx_alname, rx_data+1);
}

void creat_alarm() {
char pwd[500] = {0};

        if(!fork()) {
                getcwd (pwd, 500);
                strcat (pwd, "/my_action");
                execl(pwd, "my_action", rx_alname, rx_secs, NULL);
        }
}

int main (int argc, char *argv[])
{

  int i, j, shm_id;
  void *shm_space = NULL;

  if (!fork ())
    {
      // DO IT AS A DEMON. TODO
      setsid ();
      shm_id = shm_unlink ("/SHM_NNN");
      shm_id = shm_open ("/SHM_NNN", O_CREAT | O_RDWR, 0777);
      if (shm_id < 0)
        {
          perror ("shm_open");
          exit (1);
        }
      ftruncate (shm_id, DATA_LEN);
      shm_space = mmap (NULL, sizeof (DATA_LEN), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
      while (1)
        {
          while ((*(char *) shm_space) != '#');
          strcpy (rx_data, (char *) shm_space);
          get_secs_alname (rx_data);
          creat_alarm();
          rx_data[0] = 0;
          *(char *) shm_space = 0;
        }
    }
}

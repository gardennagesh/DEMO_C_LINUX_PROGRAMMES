/************************************ THIS IS MQ_CLIENT.c ******************************************************************
 This File  : mq_client.c 
 Programmer : Nagesh Nanjundachari at garden.nagesh@gmail.com 

 Task       : Simple programme to  demo how POSIX-MQ with ONE-message exchanged without SemaPhores.
              This programme uses SIGUSR1 signal for  notification to indicate arrival of data at client.
              mq_client.c programme  sends strings "ODD_EVENT" or "EVE_EVENT" to mq_server.c programme.  
              mq_client.c uses its pid as priority of MQ communciation concept.
              mq_server.c acknowledges with strings  "11111" for odd_event  and "22222" for even_event.
              mq_server.c uses PID of client to acknowledge to client.

 CompilE and USAGE: 

 cc mq_server.c -lrt -o mq_server; ./mq_server &  (Run server first as background process)
 cc mq_client.c -lrt -o mq_client; ./mq_client   (Next run client, which send events based on random number).

 If mq_server running do not run one more time. Else.......
 KILL mq_server before re-starting new mq_server. There should be one instance of mq_server.
*********************************************************************************************************************/


//EXECUTE THIS PROGRAMME AFTER RUNNING MQ_SERVER.C


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>

// Strings ODD_EVENT  or EVE_EVENT  length is 9
#define BUFF_LEN     10

char tx_data[BUFF_LEN];
char rx_data[BUFF_LEN];
struct sigaction mq_notif;
volatile int ack_recvd = 1;
mqd_t mq_id;


void
msg_arrived (int sig)
{

  if (mq_receive (mq_id, rx_data, BUFF_LEN, NULL) < 0)
    perror ("mq_recv");
  ack_recvd = 1;
  fprintf (stdout, "ACK MSG RECVD: %s\n", rx_data);
}

int
main (int argc, char **argv)
{

  unsigned int pid_as_priority = 0;
  struct mq_attr present_attr;


  pid_as_priority = getpid ();

  mq_id = mq_open ("/MQ_NN", O_RDWR);
  if (mq_id < 0)
    {
      perror ("mq_open");
      exit (1);
    }
  // Register for message arrival notification.
  mq_notif.sa_handler = &msg_arrived;
  sigaction (SIGUSR1, &mq_notif, NULL);

  fprintf (stdout, "client process will send 2 sec delayed msg. \n");

  while (1)
    {
      // random event generator. and make message string.
      if (!(random () % 2))
	strcpy (tx_data, "ODD_EVENT");
      else
	strcpy (tx_data, "EVE_EVENT");

      // Send message 2 sec delay.
      sleep (2);

      // Wait for no messages on MQ before putting message on MQ.
      while (present_attr.mq_curmsgs)
	mq_getattr (mq_id, &present_attr);
      if (mq_send (mq_id, tx_data, sizeof (tx_data) -1, pid_as_priority) < 0)
	perror ("mq_send");
      ack_recvd = 0;
      while (!ack_recvd);
    }
  return 0;
}

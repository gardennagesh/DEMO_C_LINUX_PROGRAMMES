/************************************THIS IS MQ_SERVER.c ******************************************************************
 This File  : mq_server.c 
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


//EXECUTE THIS PROGRAMME BEFORE RUNNING MQ_CLIENT.C


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

char rx_data[BUFF_LEN];
char tx_data[BUFF_LEN];

int
main (int argc, char **argv)
{

  mqd_t mq_id;
  pid_t pid_as_priority;
  struct mq_attr org_attr, present_attr;

  org_attr.mq_flags = 0;
  org_attr.mq_maxmsg = 1;
  org_attr.mq_msgsize = BUFF_LEN - 1;
  org_attr.mq_curmsgs = 0;

  mq_id = mq_unlink ("/MQ_NN");
  mq_id = mq_open ("/MQ_NN", O_CREAT | O_RDWR, 00777, &org_attr);
  if (mq_id < 0)
    perror ("mq_open");

  fprintf (stdout, "Notify proc is ready\n");

  while (1)
    {
      // receive message from mq_client.c process
      if (mq_receive (mq_id, rx_data, BUFF_LEN, &pid_as_priority) < 0)
	perror ("mq_receive");
      else
	{
	  // print data exchange  on stdout.
	  fprintf (stdout, "MSG RECEIVED FROM MQ_CLIENT.C PROCESS: %s\n", rx_data);

	  //Make acknowledegment number based on received msg.
	  if (strstr (rx_data, "ODD_EVENT") != NULL)
	    strcpy (tx_data, "111111");
	  if (strstr (rx_data, "EVE_EVENT") != NULL)
	    strcpy (tx_data, "22222");

	  // Put acknowledgement-number on MQ so that mq_client.c process reads.
	  mq_send (mq_id, tx_data, sizeof (tx_data) - 1, 0);

	  // Make sure that the message is on MQ and then notify mq_client.c process.
	  while (!present_attr.mq_curmsgs)
	    mq_getattr (mq_id, &present_attr);

	  // Notify that Acknowledge is sent to mq_client.c proc.
	  kill (pid_as_priority, SIGUSR1);

	  // wait for zero message on MQ so that read next new message sent by mq_client.c proc.

	  while (present_attr.mq_curmsgs)
	    mq_getattr (mq_id, &present_attr);
	}
    }
  return 0;
}

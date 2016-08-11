/* FILE: udp.c  
 * VERSION: 2.3k 2004_09_20
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "cfdp_code.h"

#define  ASCII_TERMINATOR  0

/* Module variables */
static boolean                 m_debug = NO;
static struct sockaddr_in      m_my_sockaddr;
static int                     m_my_sockfd;
static struct sockaddr_in      m_partner_sockaddr;



/*=r=************************************************************************/
boolean udp__open (int port_number)
   {
   /*------------------------------------------------------------*/
     if ((port_number < MIN_PORT_NUMBER) || (port_number > MAX_PORT_NUMBER))
       {
         msg__ ("<ERROR> UDP: Invalid port number.\n");
         return (0);
       }

     if (m_debug)
       msg__ ("UDP: will receive input via port #%u on the localhost.\n", 
              port_number);

     /* Initialize the data structure for this port */
     memset ((void *) &m_my_sockaddr,   0,   sizeof (m_my_sockaddr));
     m_my_sockaddr.sin_family = AF_INET;
     m_my_sockaddr.sin_addr.s_addr = htonl (INADDR_ANY);
     m_my_sockaddr.sin_port = htons (port_number);

     /*---------------------*/
     /* Create a UDP socket */
     /*---------------------*/
     if ((m_my_sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
       {
         msg__ ("<ERROR> UDP: Socket creation failed.\n");
         return (0);
       }

     /*------------------------------------*/
     /* Bind that socket to my port number */
     /*------------------------------------*/
     if (bind (m_my_sockfd, (struct sockaddr *) &m_my_sockaddr, 
               sizeof (m_my_sockaddr)) < 0)
       {
         msg__ ("<ERROR> UDP: Socket bind failed.\n");
         return (0);
       }

     return (1);
   }



/*=r=************************************************************************/
void udp__choose_partner (char *ip_address, int port_number)
{
  /*------------------------------------------------------------*/
  /* Initialize the data structure that describes my UDP partner */
  if (m_debug)
    msg__ ("UDP: initializing comm with partner at port #%u on %s.\n",
           port_number, ip_address);
  memset ((void *) &m_partner_sockaddr, 0, sizeof (m_partner_sockaddr));
  m_partner_sockaddr.sin_family = AF_INET;
  m_partner_sockaddr.sin_addr.s_addr = inet_addr (ip_address);
  m_partner_sockaddr.sin_port = htons (port_number);
}



/*=r=************************************************************************/
void udp__write_data (DATA msg_out)
   {
     int            count;
     int            msg_length;
     void          *msg_ptr;
   /*------------------------------------------------------------*/
     msg_length = msg_out.length;
     msg_ptr = (void *) msg_out.content;

     count = sendto (m_my_sockfd, msg_ptr, msg_length, 0, 
                     (const struct sockaddr *) &m_partner_sockaddr, 
                     sizeof (m_partner_sockaddr));
     if (count != msg_length)
       {
         msg__ ("<FATAL> UDP: Socket output failed (%d of %u bytes sent).\n", 
                 count, msg_length);
         exit (1);
       }

     /*     sleep (1); */
   }


/*=r=************************************************************************/
void udp__write_string (char *msg_out)
   {
     int            msg_length;
     void          *msg_ptr;
   /*------------------------------------------------------------*/
     msg_length = strlen (msg_out);
     msg_ptr = (void *) msg_out;
     if (sendto (m_my_sockfd, msg_ptr, msg_length, 0,
                 (const struct sockaddr *) &m_partner_sockaddr, 
                 sizeof (m_partner_sockaddr)) != msg_length)
       {
         msg__ ("<FATAL> UDP: Socket output failed.\n");
         exit (1);
       }
   }



/*=r=************************************************************************/
boolean udp__read_string_with_timeout (int timeout_in_millisecs, char *msg_in)
   {
     int                     byte_count;
     fd_set                  fdvar;
     boolean                 was_data_received = NO;
     int                     ready_count;
     static struct timeval   timeout;
   /*------------------------------------------------------------*/
     timeout.tv_sec = 0;
     timeout.tv_usec = timeout_in_millisecs * 1000;
     FD_ZERO (&fdvar);
     FD_SET (m_my_sockfd, &fdvar);
     ready_count = select (m_my_sockfd+1, &fdvar, (fd_set *) 0, 
                           (fd_set *) 0, &timeout);
     if (ready_count < 0)
       {
         msg__ ("<FATAL> UDP: 'Select' call failed.\n");
         exit (1);
       }
     else if (ready_count == 0)
       /* Timeout */
       ;
     else
       /* Data is ready; read it */
       {
         byte_count = recvfrom (m_my_sockfd, msg_in, MAX_DATAGRAM_LENGTH, 0,
                       (struct sockaddr *) 0, (int *) 0);
         if (byte_count < 0)
           {
             msg__ ("<FATAL> UDP: Socket input failed.\n");
             exit (1);
           }
         msg_in[byte_count] = 0;
         was_data_received = YES;
       }

     return (was_data_received);
   }



/*=r=************************************************************************/
boolean udp__read_data_with_timeout (int timeout_in_millisecs, 
                                     DATA *msg_in_ptr)
   {
     int                     byte_count;
     fd_set                  fdvar;
     int                     ready_count;
     static struct timeval   timeout;
     boolean                 was_data_received = NO;
   /*------------------------------------------------------------*/
     timeout.tv_sec = 0;
     timeout.tv_usec = timeout_in_millisecs * 1000;
     FD_ZERO (&fdvar);
     FD_SET (m_my_sockfd, &fdvar);
     ready_count = select (m_my_sockfd+1, &fdvar, (fd_set *) 0, 
                           (fd_set *) 0, &timeout);
     if (ready_count < 0)
       {
         msg__ ("<FATAL> UDP: 'Select' call failed.\n");
         exit (1);
       }
     else if (ready_count == 0)
       /* Timeout */
       ;
     else
       /* Data is ready; read it */
       {
         byte_count = recvfrom (m_my_sockfd, msg_in_ptr->content, 
                                MAX_DATAGRAM_LENGTH, 0,
                                (struct sockaddr *) 0, (int *) 0);
         if (byte_count < 0)
           {
             msg__ ("<FATAL> UDP: Socket input failed.\n");
             exit (1);
           }
         msg_in_ptr->length = byte_count;
         was_data_received = YES;
       }

     return (was_data_received);
   }



/*#define SELF_TEST 1*/
#ifdef SELF_TEST

#define PRINTF printf

/*=r=************************************************************************/
static boolean m__is_there_a_msg_from_stdin (void)
/* WHAT IT DOES:  Returns immediately.  Indicates whether or not a message is
 *   available via stdin.  (Does not read the message).
 */
   {
     fd_set                  fdvar;
     static boolean          is_msg_waiting;
     int                     ready_count;
     static struct timeval   timeout;
   /*------------------------------------------------------------*/
     is_msg_waiting = NO;
     timeout.tv_sec = 0;
     timeout.tv_usec = 0;
     FD_ZERO (&fdvar);
     FD_SET (STDIN_FILENO, &fdvar);
     ready_count = select (STDIN_FILENO+1, &fdvar, (fd_set *) 0, 
                           (fd_set *) 0, &timeout);
     if (ready_count < 0)
       {
         msg__ ("<FATAL> UDP: 'Select' call failed.\n");
         exit (1);
       }
     else if (ready_count == 0)
       /* Timeout */
       ;
     else if (FD_ISSET (STDIN_FILENO, &fdvar))
       is_msg_waiting = YES;
     else
       /* No msg at stdin */
       ;

     return (is_msg_waiting);
   }



/*=r=************************************************************************/
int main (int argc, char *argv[])
   {
#define  MY_DEFAULT_PORT  2500
#define  PARTNER_DEFAULT_PORT  2501
     DATA                    data_from_partner;
     DATA                    data_to_partner;
     int                     msg_count;
     char                    msg_from_partner [MAX_DATAGRAM_LENGTH+1];
     char                    msg_from_user [MAX_DATAGRAM_LENGTH+1];
     int                     my_port_number;
     int                     partner_port_number;
     int                     sockfd;
   /*------------------------------------------------------------*/
     PRINTF ("Program: Udp self-test version 1.1\n");

   /* Determine my port number */
   if (argc > 1)
     sscanf (argv[1], "%i", &my_port_number);
   else
     my_port_number = MY_DEFAULT_PORT;
   PRINTF ("My port number is %d.\n", my_port_number);

   /* Determine partner's port number */
   if (argc > 2)
     sscanf (argv[2], "%i", &partner_port_number);
   else
     partner_port_number = PARTNER_DEFAULT_PORT;
   PRINTF ("Partner's port number is %d.\n", partner_port_number);
   
   udp__open (my_port_number);
   udp__choose_partner ("128.183.156.16", partner_port_number);
   PRINTF ("Socket has been created; ready for messages...\n");

   PRINTF ("First, 3 messages using the 'data' methods...\n");
   for (msg_count=0; msg_count<3; )
     {
       while (udp__read_data_with_timeout (100, &data_from_partner))
         {
           msg_count ++;
           strncpy (msg_from_partner, data_from_partner.content,
                    data_from_partner.length);
           msg_from_partner[data_from_partner.length] = ASCII_TERMINATOR;
           PRINTF ("Data from partner:  Length=%d; content='%s'.\n", 
                   data_from_partner.length, msg_from_partner);
         }
       if (m__is_there_a_msg_from_stdin ())
         {
           fgets (msg_from_user, MAX_DATAGRAM_LENGTH, stdin);
           msg_from_user[strlen(msg_from_user)-1] = ASCII_TERMINATOR;
           PRINTF ("Msg_to_send:  %s.\n", msg_from_user);
           data__init (&data_to_partner);
           data__append_ascii (&data_to_partner, msg_from_user);
           udp__write_data (data_to_partner);
         }
     }

   PRINTF ("Second, unlimited messages using the 'string' methods...\n");
   for (;;)
     {
       while (udp__read_string_with_timeout (100, msg_from_partner))
         PRINTF ("String_from_partner:  %s.\n", msg_from_partner);
       if (m__is_there_a_msg_from_stdin ())
         {
           fgets (msg_from_user, MAX_DATAGRAM_LENGTH, stdin);
           msg_from_user[strlen(msg_from_user)-1] = ASCII_TERMINATOR;
           PRINTF ("Msg_to_send:  %s.\n", msg_from_user);
           udp__write_string (msg_from_user);
         }
     }

   PRINTF ("Bye.\n");
   }

#endif

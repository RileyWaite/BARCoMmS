/* FILE: usleep.c 
 * VERSION: 2.3k 2004_09_20
 * SPECS:  see 'usleep.h'
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include "cfdp_code.h"






/*=r=************************************************************************/
void usleep__milliseconds (int how_many)
   {
     static boolean           has_error_been_reported = NO;
     static struct timeval    timeout;
   /*------------------------------------------------------------*/
     timeout.tv_sec = how_many / 1000;
     timeout.tv_usec = (how_many % 1000) * 1000;
     if (select (0, (fd_set *) 0, (fd_set *) 0, (fd_set *) 0, &timeout) < 0)
       if (!has_error_been_reported)
         {
           msg__ ("<ERROR> 'usleep__milliseconds' failed.\n");
           msg__ ("<WARNING> This error message will not be repeated.\n");
           has_error_been_reported = YES;
         }
   }



/*=r=************************************************************************/
void usleep__microseconds (u_int_4 how_many)
   {
     static boolean           has_error_been_reported = NO;
     static struct timeval    timeout;
   /*------------------------------------------------------------*/
     timeout.tv_sec = how_many / 1000000;
     timeout.tv_usec = (how_many % 1000000);
     if (select (0, (fd_set *) 0, (fd_set *) 0, (fd_set *) 0, &timeout) < 0)
       if (!has_error_been_reported)
         {
           msg__ ("<ERROR> 'usleep__microseconds' failed.\n");
           msg__ ("<WARNING> This error message will not be repeated.\n");
           has_error_been_reported = YES;
         }
   }



/*#define SELF_TEST 1*/
#ifdef SELF_TEST

#define PRINTF msg__


/*=r=************************************************************************/
main ()
   {
     int          milliseconds;
     u_int_4      microseconds;
     char         string [17];
   /*------------------------------------------------------------*/
     for (;;)
       {
         PRINTF ("Enter number of milliseconds to wait (0 to quit) : ");
         fgets (string, 16, stdin);
         milliseconds = atoi (string);
         if (milliseconds == 0)
           break;
         else
           usleep__milliseconds (milliseconds);
       }

     for (;;)
       {
         PRINTF ("Enter number of MICROSECONDS to wait (0 to quit) : ");
         fgets (string, 16, stdin);
         microseconds = atoi (string);
         if (microseconds == 0)
           break;
         else
           usleep__microseconds (microseconds);
       }

     PRINTF ("Bye.\n");
   }

#endif

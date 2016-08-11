/* FILE: test_cfdp.c -- a program that runs tests of my CFDP program.
 *   Intended to be run something like this:  
 *         cfdp_test < test.in | tee test.out
 *   i.e. the program reads directives from stdin, allowing input files to
 *   be used as test scripts.  
 * SPECS:  see test_cfdp.h
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */
/* LOG:
  2003_12_28
      The terms 'A' and 'B' are used to represent two CFDP nodes (the first
    two nodes registered by the test script).  'Puts' are file transfers from
    A to B; 'gets' are from B to A.
  2003_12_29
      Source files (for puts/gets) are created on-the-fly.  The size of the
    file is stored in 'm_file_size' (and can be modified via directive).
    Again, for each put/get, the required source file is created on-the-fly,
    and filled with random data.
      The file names are _____1_____, ____2____, ____3____, ... (the
    prefix and suffix are fixed in '#defines').
      A test run consists of one or more sub-tests.  Each sub-test contains
    puts and gets, followed by one of the 'verify' directives.  At the
    end of each sub-test, all the files are cleared out.
  2003_12_30
      This program can now modify some MIB settings on the fly (via the
    new 'mib' directive).
      Multiple 'puts' and/or 'gets' can now be requested with a single
    directive (e.g. "put*10" requests 10 'puts').
      This program now deletes any src/dest files leftover from previous 
    runs at the start of the current run.  (leftover files had been found to
    distort the test results).
  2004_01_02 
      The top-level input can now run sub-scripts (via the "run" directive).
      Added the 'm__failure' routine (to ensure that all failures result in
      a message to 'stderr').
  2004_02_24
      Added a 'system' directive (e.g. "system ls -sal" to see a directory).
*/

#define INTERNAL_VERSION "2.0v 2004_01_05"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include "test_cfdp.h"

#define ASSERT(condition) if (!(condition)) { \
   printf ("Assertion failed at line %u.\n", __LINE__); \
   m__failure ("assertion failed"); }
#define A 0   /* Node A */
#define B 1   /* Node B */
#define boolean char
#define MAX_MESSAGE_LENGTH 80
#define NO 0
#define STRING_TERMINATOR 0
#define u_int_1 unsigned char
#define u_int_2 unsigned int
#define u_int_4 unsigned long int
#define YES 1

typedef struct
{
  FILE      *fp_from_node;
  FILE      *fp_to_node;
  char       id [MAX_ID_LENGTH];
} CFDP_NODE;

typedef enum { CLASS_1, CLASS_2 } CLASS;

static boolean        m_debug_pipes = NO;
static FILE          *m_fp_for_input;
static int            m_line_number = 0;
static int            m_top_level_line_number = 0;
static CFDP_NODE      m_node [MAX_NODES];
static int            m_node_count = 0;
static u_int_4        m_source_file_size = DEFAULT_SOURCE_FILE_SIZE;
static char           m_sub_script [MAX_FILENAME_LENGTH];
static u_int_2        m_timeout = 600;
static int            m_transfer_count = 0;


/*------------------*/
/* Utility routines */
/*------------------*/


/*=r=************************************************************************/
static boolean m__are_these_files_identical (char *f1, char *f2)
     /* WHAT IT DOES:  Returns 1 if the contents of the two files match;
      *   0 otherwise.
      */
{
  int           chr1;
  int           chr2;
  boolean       do_they_match;
  FILE          *fp1;
  FILE          *fp2;
  /*------------------------------------------------------------*/

  /*-----------------*/
  /* Open both files */
  /*-----------------*/

  if ((fp1 = fopen (f1, "rb")) == NULL)
    {
      printf ("<ERROR> Unable to open file '%s'.\n", f1);
      return (0);
    }

  if ((fp2 = fopen (f2, "rb")) == NULL)
    {
      printf ("<ERROR> Unable to open file '%s'.\n", f2);
      return (0);
    }

  /*------------------------*/
  /* Compare their contents */ 
  /*------------------------*/

  for (;;)
    {
      chr1 = getc (fp1);
      chr2 = getc (fp2);
      if (chr1 != chr2)
        /* Mismatch */
        {
          do_they_match = NO;
          break;
        }
      if (chr1 == EOF)
        /* Done; success */
        {
          do_they_match = YES;
          break;
        }
    }

  fclose (fp1);
  fclose (fp2);
  return (do_they_match);
}



/*=r=************************************************************************/
static void m__convert_string_to_uppercase (char *string)
   {
     int            i;
   /*------------------------------------------------------------*/
     for (i=0; i<strlen(string); i++)
       string[i] = toupper (string[i]);
   }



/*=r=************************************************************************/
static boolean m__create_random_file (char *filename, u_int_4 size)
     /* WHAT IT DOES:  Creates a file with the given filename, writes
      *   'size' bytes into it (each byte has a random value), and closes 
      *   the file.
      * RETURN STATUS:  1 if successful; 0 otherwise.
      */
{
  int                 attempts;
  u_int_1             byte;
  boolean             file_created;
  FILE               *fp;
  u_int_4             i;
  /*------------------------------------------------------------*/

  file_created = NO;
  attempts = 0;
  while (!file_created && (attempts < 10))
    {
      if ((fp = fopen (filename, "w")) != NULL)
	file_created = YES;
      else
	{
	  attempts ++;
	  printf ("<WARNING> Unable to open '%s'.\n", filename);
	  printf ("(will try again in 10 seconds...)\n");
	  fflush (stdout);
	  sleep (10);
	}
    }

  if (file_created)
    /* Populate it with random data */
    {
      for (i=0; i<size; i++)
	{
	  byte = rand() % 256;
	  fprintf (fp, "%c", byte);
	}
      fclose (fp);
    }

  return (file_created);
}



/*=r=************************************************************************/
static void m__delete_file (char *filename)
     /* WHAT IT DOES:  Deletes the specified file from disk. */
{
  char           cmd [128];
  /*------------------------------------------------------------*/
  sprintf (cmd, OS_SYNTAX_FOR_DELETING_A_FILE, filename);
  strcat (cmd, "\n");
  system (cmd);
}



/*=r=************************************************************************/
static void m__failure (char *reason)
     /* WHAT IT DOES:  Exits the program (writes a message or two first). */
{
  char              string [256];
  char              script_info [MAX_FILENAME_LENGTH];
  /*------------------------------------------------------------*/

  system ("date\n");
  
  if (strlen(m_sub_script) > 0)
    sprintf (script_info, " of '%s'", m_sub_script);
  else
    strcpy (script_info, "\0");

  sprintf (string, "<FAILURE> %s\n"
           "(at line #%u%s)", reason, m_line_number, script_info);

  printf ("%s\n", string);
  printf ("Bye.\n");
  exit (1);
}



/*=r=*************************************************************************/
static void m__fgets (char *line, int max_length, FILE *fp)
     /* WHAT IT DOES:  Looks like 'fgets' from the outside, but on the
      *   inside it performs an unbuffered input (rather than a buffered
      *   input).
      */
{
  char             current;
  boolean          end_of_file;
  int              fd;
  int              line_length;
  int              status;
  /*------------------------------------------------------------*/

  fd = fileno (fp);

  end_of_file = NO;
  line_length = 0;
  current = '?';
  line[0] = '\0';

  while ((current != '\n') && !end_of_file)
    {
      status = read (fd, &current, 1);
      if (status == -1)
	m__failure ("'read' failed in m__fgets");
      else if (status == 0)
	end_of_file = YES;
      else
	/* Append this char to the line */
	{
	  if (line_length >= (MAX_LINE_LENGTH - 1))
	    m__failure ("Input from pipes exceeded max-length");
	  line[line_length] = current;
	  line_length ++;
	  line[line_length] = '\0';
	}
    }

  if (m_debug_pipes)
    printf ("Pipe input: %s", line);
}



/*=r=************************************************************************/
static void m__remove_any_comment (char *line, char marker)
     /* ASSUMES:  Within any given line, the char 'marker' indicates that the 
      *   rest of the line is a comment.
      * WHAT IT DOES:  Removes any comment from the given line (truncates
      *   the string in front of the first marker).
      */
{
  int              i;
  /*------------------------------------------------------------*/

  ASSERT (line != NULL);

  for (i=0; i<strlen(line); i++)
    if (line[i] == marker)
      line[i] = STRING_TERMINATOR;
}



/*=r=************************************************************************/
static void m__remove_trailing_whitespace (char *string)
     /* WHAT IT DOES:  Removes all white-space from end of given string. */
{
  int          i;
  /*------------------------------------------------------------*/

  ASSERT (string != NULL);

  if (strlen(string) == 0)
    return;
  
  for (i=strlen(string)-1; i>=0; i--)
    {
      if (!isspace(string[i]))
        /* This char is not white-space; we're done */
        break;
      string[i] = STRING_TERMINATOR;
    }
}



/*=r=************************************************************************/
void m__sleep_milliseconds (int how_many)
     /* WHAT IT DOES:  Sleeps for the specified number of milliseconds */
{
  static boolean           has_error_been_reported = NO;
  static struct timeval    timeout;
  /*------------------------------------------------------------*/

  timeout.tv_sec = how_many / 1000;
  timeout.tv_usec = (how_many % 1000) * 1000;
  if (select (0, (fd_set *) 0, (fd_set *) 0, (fd_set *) 0, &timeout) < 0)
    if (!has_error_been_reported)
      {
        printf ("<ERROR> 'usleep__milliseconds' failed.\n");
        printf ("<WARNING> This error message will not be repeated.\n");
        has_error_been_reported = YES;
      }
}



/*---------------------------*/
/* Program-specific routines */
/*---------------------------*/


/*=r=************************************************************************/
static void m__clear_between_test_runs (void)
     /* WHAT IT DOES:  Deletes all the files have been created since the
      *   last call to this routine, and resets the info that is used
      *   to determine which file transfers need to be verified.
      */
{
  char         dest_filename [MAX_FILENAME_LENGTH+1];
  int          i;
  char         source_filename [MAX_FILENAME_LENGTH+1];
  /*------------------------------------------------------------*/

  /* Delete all source and destination files */
  for (i=0; i<m_transfer_count; i++)
    {
      sprintf (source_filename, "%s%2.2u%s", 
               FILENAME_PREFIX_FOR_SOURCE, 
               i,
               FILENAME_SUFFIX_FOR_SOURCE);
      sprintf (dest_filename, "%s%2.2u%s",
               FILENAME_PREFIX_FOR_DESTINATION,
               i,
               FILENAME_SUFFIX_FOR_DESTINATION);
      m__delete_file (source_filename);
      m__delete_file (dest_filename);
    }
  
  /* There are no longer any transfers to verify */
  m_transfer_count = 0;
}



/*=r=************************************************************************/
static char *m__destination_filename (int number)
     /* WHAT IT DOES:  Generates (and returns) the appropriate name
      *   for the destination file associated with the given number.
      */
{
  static char         filename [MAX_FILENAME_LENGTH];
  /*------------------------------------------------------------*/
  sprintf (filename, "%s%02u%s", 
           FILENAME_PREFIX_FOR_DESTINATION, 
           number,
           FILENAME_SUFFIX_FOR_DESTINATION);
  return (filename);
}



/*=r=************************************************************************/
static char *m__source_filename (int number)
     /* WHAT IT DOES:  Generates (and returns) the appropriate name
      *   for the source file associated with the given number.
      */
{
  static char         filename [MAX_FILENAME_LENGTH];
  /*------------------------------------------------------------*/
  sprintf (filename, "%s%02u%s", 
           FILENAME_PREFIX_FOR_SOURCE, 
           number,
           FILENAME_SUFFIX_FOR_SOURCE);
  return (filename);
}



/*=r=************************************************************************/
static boolean m__is_this_cfdp_node_registered (char *node)
     /* WHAT IT DOES:  Returns YES if the given node (e.g. "23") is 
      *   already registered with this program; otherwise, NO.
      */
{
  int              i;
  /*------------------------------------------------------------*/
  for (i=0; i<m_node_count; i++)
    if (!strcmp (m_node[i].id, node))
      /* Found a matching entry */
      return (YES);

  return (NO);
}



/*=r=*************************************************************************/
static boolean m__wait_for_ack_of_message (FILE *fp)
{
  int                     fd;
  fd_set                  fdvar;
  char                    input [80];
  int                     ready_count;
  static struct timeval   timeout;
  boolean                 was_ack_received;
  /*------------------------------------------------------------*/

  fd = fileno (fp);

  was_ack_received = NO;

  timeout.tv_sec = 10;
  timeout.tv_usec = 0;
  FD_ZERO (&fdvar);
  FD_SET (fd, &fdvar);
  ready_count = select (fd+1, &fdvar, (fd_set *) 0, 
			(fd_set *) 0, &timeout);
  if (ready_count < 0)
    m__failure ("'Select' call failed in 'wait_for_ack'");
  else if (ready_count == 0)
    /* Timeout */
    ;
  else if (FD_ISSET (fd, &fdvar))
    {
      m__fgets (input, 80, fp);
      if (input[0] == '.')
	was_ack_received = YES;
      else
	{
	  printf ("Expected ack ('.'); got '%s'.\n", input);
	  fflush (stdout);
	}
    }
  else
    ;

  return (was_ack_received);
}



/*=r=************************************************************************/
static void m__deliver_message_to_cfdp_node (int which_node, char *message)
     /* WHAT IT DOES:  Delivers the given message to the specified node
      *   (via whichever named pipe is registered for the node).
      *   Delivery = send the message + wait for acknowledgement back.
      * NOTE:  This routine adds a newline to the given message.
      */
{
  FILE           *fp;
  /*------------------------------------------------------------*/

  if (m_debug_pipes)
    {
      printf ("   Sending '%s' to node #%u (id=%s).\n", message, which_node,
	      m_node[which_node].id);
      fflush (stdout);
    }

  fp = m_node[which_node].fp_to_node;
  fprintf (fp, "%s\n", message);
  fflush (fp);

  /* Kludge:
   *   When 2 messages are written to a named-pipe in quick succession,
   *   the receiver doesn't see the second message.
   *   I can't explain why.
   *   Anyway, there is no harm in waiting one second after initiating a
   *   file transfer (it will take at least one second to complete).
   */
  if (!strncmp (message, "put", 3))
    /* ^^^ sleep (1); */ ;
  
  fp = m_node[which_node].fp_from_node;
  if (!m__wait_for_ack_of_message (fp))
    m__failure ("CFDP node did not ack my message.\n");
  if (m_debug_pipes)
    {
      printf ("   Got ack from CFDP node.\n");
      fflush (stdout);
    }
}



/*=r=************************************************************************/
static void m__help (void)
     /* WHAT IT DOES:  Outputs helpful info for the user. */
{
#define PP printf
  /*------------------------------------------------------------*/
  PP ("\n-------------------- Help --------------------\n"
      "   There are two CFDP nodes, 'A' and 'B'.\n"
      "   By default, file transfers use Service Class 2.  Directives:\n"
      "Clear_Between_Tests -- deletes all test files\n"
      "Get            -- send one file from B to A\n"
      "Get*__         -- 'n' gets (e.g. 'get*10')\n"
      "Get_1          -- send one file from B to A (Class 1)\n"
      "Get_And_Put    -- send one file in each direction\n"
      "Get_And_Put*__ -- interleave 'n' files in each direction\n"
      "Link_Sim ____  -- send dir to the Link Simulator\n"
      "MIB ____       -- send dir to the MIB\n"
      "Node ___       -- register a CFDP node (e.g. 'node 23')\n"
      "Put            -- send one file from A to B\n"
      "Put*__         -- 'n' puts (e.g. 'put*20')\n"
      "Put_1          -- send one file from A to B (Class 1)\n"
      "Run ___        -- run a script from inside this script\n"
      "Send_To_A ___  -- sends a message to node A\n"
      "Send_To_B ___  -- sends a message to node B\n"
      "Source_File_Size ___ -- specify size of file to be transferred\n"
      "Set_Timeout ____  -- sets max wait time (in seconds) when \n"
      "                  waiting for trans completion/cancellation.\n"
      "Transaction_Details ______ -- detailed status for one transaction.\n"
      "Verify_File_Transfers -- verify that each destination file is \n"
      "                  identical to its associated source file.\n"
      "Verify_Condition_Code ___ -- verify that the last transaction at \n"
      "                  each node completed with this Condition Code.\n"
      "Verify_Condition_Code_At_A ___ -- verifies that the last transaction \n"
      "                  at node A completed with this Condition-Code.\n"
      "Verify_Condition_Code_At_B ___ -- verifies that the last transaction \n"
      "                  at node B completed with this Condition-Code.\n"
      "Verify_Abandoned __ -- verifies that at all nodes, the last\n"
      "                  completed transaction was abandoned (or not).\n"
      "Verify_Abandoned_At_A -- verifies that at node A, the last \n"
      "                  completed transaction was abandoned.\n"
      "Verify_Abandoned_At_B -- verifies that at node B, the last \n"
      "                  completed transaction was abandoned.\n"
      "Verify_Transactions_Exist -- verifies that there is at least one\n"
      "                  active transaction at each node.\n"
      "Wait ___       -- wait 'n' seconds\n"
      "Wait_For_Transaction_Completion -- wait for all trans to finish\n"
      "Wait_For_Transaction_Cancellation -- wait for one trans (at any node)\n"
      "                  to be cancelled.\n"
      );
}



/*=r=************************************************************************/
static void m__request_a_put (CLASS class, 
                              int source_number, char *source_filename,
                              int dest_number, char *dest_filename)
     /* WHAT IT DOES:  Generates the appropriate message to tell the specified
      *   source node to send the specified source-file to the specified
      *   destination node as the specified destination-file, and
      *   delivers the message to the Src node.
      *   'class' chooses either the Class 1 or Class 2 Service Class.
      *   The typical message is "p2 source.in 24 dest.out".
      */
{
  static char               message [MAX_MESSAGE_LENGTH];
  char                      optional [32];
  /*------------------------------------------------------------*/
  /* Generate the appropriate message (to request a Put from src to dest) */
  ASSERT ((class == CLASS_1) || (class == CLASS_2));
  strcpy (message, "put ");
  if (class == CLASS_1)
    strcpy (optional, "-class1 ");
  else
    strcpy (optional, "\0");
  sprintf (message, "put %s%s %s %s", 
           optional, source_filename, 
           m_node[dest_number].id, dest_filename);
  
  /* Deliver it */
  m__deliver_message_to_cfdp_node (source_number, message);
  printf ("   --> %s: %s\n", m_node[source_number].id, message);

}



/*=r=*************************************************************************/
static boolean m__wait_for_message_from_cfdp_node (int which_node, char *msg)
{
  int                     fd;
  FILE                   *fp;
  fd_set                  fdvar;
  int                     ready_count;
  static struct timeval   timeout;
  boolean                 was_msg_received;
  /*------------------------------------------------------------*/

  fp = m_node[which_node].fp_from_node;
  fd = fileno (fp);

  was_msg_received = NO;

  timeout.tv_sec = 10;
  timeout.tv_usec = 0;
  FD_ZERO (&fdvar);
  FD_SET (fd, &fdvar);
  ready_count = select (fd+1, &fdvar, (fd_set *) 0, 
			(fd_set *) 0, &timeout);
  if (ready_count < 0)
    m__failure ("'Select' call failed in 'wait_for_message'");
  else if (ready_count == 0)
    /* Timeout */
    ;
  else if (FD_ISSET (fd, &fdvar))
    {
      m__fgets (msg, 80, fp);
      was_msg_received = YES;
    }
  else
    ;

  return (was_msg_received);
}



/*=r=************************************************************************/
static boolean m__wait_for_trans_cancellation (int timeout)
     /* WHAT IT DOES:  Waits up to 'timeout' seconds for any CFDP node
      *   to begin cancelling a transaction.
      * RETURN STATUS:  1 = success    0 = failure (timeout or read failed)
      */
{
  time_t        current_time;
  boolean       has_timeout_occurred;
  boolean       is_any_trans_being_cancelled;
  int           i;
  char          message_from_node [MAX_LINE_LENGTH];
  time_t        start_time;
  /*------------------------------------------------------------*/

  
  /* Wait up to 'timeout' seconds for any CFDP node to begin cancelling
   * a transaction.
   */
  start_time = time (NULL);
  is_any_trans_being_cancelled = NO;
  has_timeout_occurred = NO;
  while (!is_any_trans_being_cancelled && !has_timeout_occurred)
    {
      /* See if any of the nodes are cancelling a transaction */
      for (i=0; i<m_node_count; i++)
	{
	  m__deliver_message_to_cfdp_node (i, "cancelling?");
	  
	  if (!m__wait_for_message_from_cfdp_node (i, message_from_node))
	    /* This shouldn't ever happen, but it can */
	    {
	      system ("date");
	      printf ("<ERROR> No response from node #%s.\n", 
		      m_node[i].id);
	      return (0);
	    }
	  
	  m__remove_trailing_whitespace (message_from_node);
	  if (!strcmp (message_from_node, "Yes"))
	    /* Yes, this node is cancelling */
	    is_any_trans_being_cancelled = YES;
	}

      /* If no trans are being cancelled, check for timeout */
      if (!is_any_trans_being_cancelled)
	{
	  current_time = time (NULL);
	  if (current_time - start_time >= timeout)
	    {
	      has_timeout_occurred = YES;
	      printf ("<ERROR> After %u seconds, "
		      "no node has cancelled a trans.\n",
		      timeout);
	    }
	  else
	    sleep (1);
	}
    }

  return (is_any_trans_being_cancelled);
}	  



/*=r=************************************************************************/
static boolean m__wait_for_trans_completion (int timeout)
     /* WHAT IT DOES:  Waits up to 'timeout' seconds for all transactions
      *   (within all CFDP nodes) to complete.  However, if one of the 
      *   CFDP nodes fails to respond, it will return immediately.
      * RETURN STATUS:  1 = success    0 = failure (timeout or read failed)
      */
{
  time_t        current_time;
  int           i;
  char          message_from_node [MAX_LINE_LENGTH];
  time_t        start_time;
  /*------------------------------------------------------------*/


  /* Wait (up to 'timeout' seconds) for all CFDP nodes to finish 
   * all their transactions.
   */
  start_time = time (NULL);
  for (i=0; i<m_node_count; i++)
    /* Wait for each CFDP node to complete all its transactions */
    {
      printf ("   Waiting for node %u (id=%s) to complete "
              "all transactions...\n", i,
              m_node[i].id);
      for (;;)
        /* Poll this node periodically for status */
        {
          m__deliver_message_to_cfdp_node (i, 
                                        "How_many_active_transactions?");
          if (!m__wait_for_message_from_cfdp_node (i, message_from_node))
            {
	      system ("date");
              printf ("<ERROR> No response from node #%s.\n", 
                      m_node[i].id);
              return (0);
            }
          if (message_from_node[0] == '0')
            /* This node has completed all transactions */
            break;
	  else if (!isdigit (message_from_node[0]))
            printf ("<UNEXPECTED_RESPONSE_FROM_NODE> (%s)\n", 
                    message_from_node);

	  /* Check for timeout */
          sleep (1);
	  current_time = time (NULL);
	  if (current_time - start_time >= timeout)
	    /* The transactions should have completed by now. */
	    {
	      system ("date");
	      printf ("<ERROR> After %u seconds, node %s is still busy.\n",
		      timeout, m_node[i].id);
	      printf ("(it has %s transactions running)\n",
		      message_from_node);
	      m__failure ("cfdp app is hung up");
	    }
        }
    }
  
  return (1);
}



/*=r=************************************************************************/
static boolean m__check_file_transfer (void)
     /* WHAT IT DOES:  Checks to see if all file transfers were successful.
      *   ('Success' means that the source and destination files have
      *   identical contents).
      *   Returns 1 if yes; 0 if no.
      */
{
  char             dest_filename [MAX_FILENAME_LENGTH+1];
  int              i;
  char             source_filename [MAX_FILENAME_LENGTH+1];
  /*------------------------------------------------------------*/

  /* Verify that all destination files match their respective source file */
  for (i=0; i<m_transfer_count; i++)
    {
      strcpy (source_filename, m__source_filename (i));
      strcpy (dest_filename, m__destination_filename (i));

      /* Verify that src & dest files match */
      if (!m__are_these_files_identical (source_filename, dest_filename))
        {
          printf ("<ERROR> Files ('%s' & '%s') do not match.\n",
                  source_filename, dest_filename);
          return (0);
        }
    }
  return (1);
}



/*=r=************************************************************************/
static boolean m__verify_condition_code (int node, char *code)
     /* WHAT IT DOES:  Returns 1 if the specified  node completed with
      *   the given Condition-Code; otherwise, 0.  
      */
{
  char              message [80];
  char              message_from_node [80];
  /*------------------------------------------------------------*/

  /* Query this node's Condition Code */
  strcpy (message, "Last_condition_code?");
  m__deliver_message_to_cfdp_node (node, message);
  /* Get the response */
  if (!m__wait_for_message_from_cfdp_node (node, message_from_node))
    {
      printf ("<ERROR> No response from node #%s.\n", 
	      m_node[node].id);
      return (0);
    }
  m__remove_trailing_whitespace (message_from_node);
  if (strcmp (message_from_node, code))
    /* They don't match */
    {
      printf ("<ERROR> Code from node #%s is...\n"
	      "'%s' instead of '%s'.\n",
	      m_node[node].id, message_from_node, code);
      return (0);
    }

  return (1);
}



/*=r=************************************************************************/
static boolean m__verify_abandoned (int node, char *yes_or_no)
     /* WHAT IT DOES:  Returns 1 if, for the given node, the last 
      *   transaction to complete was abandoned (or not, depending on
      *   the setting of 'yes_or_no'; otherwise, 0.
      * INPUTS:  
      *   node - which node (index)
      *   yes_or_no -- "Yes" if the desired outcome is 'abandoned'.
      *             -- "No" if the desired outcome is 'not abandoned'.
      */
{
  char              message [80];
  char              message_from_node [80];
  /*------------------------------------------------------------*/

  /* Query this node's 'was last transacton abandoned?' */
  strcpy (message, "Last_transaction_abandoned?");
  m__deliver_message_to_cfdp_node (node, message);
  /* Get the response */
  if (!m__wait_for_message_from_cfdp_node (node, message_from_node))
    {
      printf ("<ERROR> No response from node #%s.\n", 
	      m_node[node].id);
      return (0);
    }
  m__remove_trailing_whitespace (message_from_node);
  if (strcmp (message_from_node, yes_or_no))
    /* They don't match */
    {
      printf ("<ERROR> 'Was last trans abandoned?' from node #%s is...\n"
	      "'%s' instead of '%s'.\n",
	      m_node[node].id, message_from_node, yes_or_no);
      return (0);
    }

  return (1);
}



/*=r=************************************************************************/
static boolean m__verify_transactions_exist (int node)
     /* WHAT IT DOES:  Returns 1 if the specified  node has at least one
      *   active transaction; otherwise, 0.
      */
{
  int               count;
  char              message [80];
  char              message_from_node [80];
  /*------------------------------------------------------------*/

  /* Query this node's active-transaction-count */
  strcpy (message, "How_many_active_transactions?");
  m__deliver_message_to_cfdp_node (node, message);

  /* Get the response */
  if (!m__wait_for_message_from_cfdp_node (node, message_from_node))
    {
      printf ("<ERROR> No response from node #%s.\n", 
	      m_node[node].id);
      return (0);
    }

  /* Convert the response to a number */
  count = atoi (message_from_node);

  /* Count should be greater than 0, but not outrageously high */
  if (count <= 0)
    {
      printf ("<ERROR> node #%s has '%s' transactions running; "
	      "should be greater than 0\n",
	      m_node[node].id, message_from_node);
      return (0);
    }
  else if (count > 500)
    {
      printf ("<ERROR> node #%s has '%s' transactions running; "
	      "should be greater than 0, but is this too many?\n",
	      m_node[node].id, message_from_node);
      return (0);
    }
    
  return (1);
}



/*=r=************************************************************************/
static boolean m__open_comm_with_node (char *id, int index)
     /* WHAT IT DOES:  Opens the comm paths for specified node, and 
      *   stores the file-pointers in the specified table index.
      */
{
  char            filename [MAX_FILENAME_LENGTH];
  int             status_of_create_pipe;
  /*------------------------------------------------------------*/

  /*--------------------------------------*/
  /* Attempt to open a file from the node */
  /*--------------------------------------*/

  sprintf (filename, GENERIC_FILENAME_FROM_NODE, id);
  printf ("Opening a file from the node (%s)... ", filename);
  fflush (stdout);

  /* Create the named-pipe (if necessary) */
  status_of_create_pipe = mkfifo (filename, S_IFIFO | 0755);
  if (status_of_create_pipe == 0)
    /* Success; created new pipe */
    ;
  else if (errno == EEXIST)
    /* Success; pipe already exists */
    ;
  else
    {
      printf ("\n<ERROR> Unable to create pipe '%s'.\n", filename);
      return (0);
    }

  /* Open the named-pipe for reading (unless already open) */
  if ((m_node[index].fp_from_node = fopen (filename, "r")) == NULL)
    {
      printf ("\n<ERROR> Unable to open pipe '%s'.\n", filename);
      return (0);
    }
  printf ("done.\n");

  /*------------------------------------*/
  /* Attempt to open a file to the node */
  /*------------------------------------*/

  sprintf (filename, GENERIC_FILENAME_TO_NODE, id);
  printf ("Opening a file to the node (%s)... ", filename);
  fflush (stdout);

  /* Create the named-pipe (if necessary) */
  status_of_create_pipe = mkfifo (filename, S_IFIFO | 0755);
  if (status_of_create_pipe == 0)
    /* Success; created new pipe */
    ;
  else if (errno == EEXIST)
    /* Success; pipe already exists */
    ;
  else
    {
      printf ("\n<ERROR> Unable to create pipe '%s'.\n", filename);
      return (0);
    }

  /* Open the named-pipe for writing */
  if ((m_node[index].fp_to_node = fopen (filename, "w")) == NULL)
    {
      printf ("\n<ERROR> Unable to open file.\n");
      fclose (m_node[index].fp_to_node);
      return (0);
    }
  printf ("done.\n");
  return (1);
}



/*=r=************************************************************************/
static boolean m__register_new_cfdp_node (char *id)
     /* WHAT IT DOES:  Attempts to register a new node with the given ID.
      *   Opens the required comm paths to this node, etc.
      * INPUT:  'ID' is the CFDP node's id-number (as a string -- e.g. "23").
      * RETURN STATUS:  1 if successful; 0 otherwise.
      */
{
  /*------------------------------------------------------------*/

  /* Make sure we haven't reach node capacity */
  if (m_node_count == MAX_NODES)
    {
      printf ("\n<ERROR> Can't have more than %u nodes.\n", MAX_NODES);
      return (0);
    }

  if (!m__open_comm_with_node (id, m_node_count))
    return (0);

  /*----------------------------------------------------------*/
  /* Success - Fill out rest of new entry to the 'node table' */
  /*----------------------------------------------------------*/
  strcpy (m_node[m_node_count].id, id);

  m_node_count ++;

  return (1);
}



/*=r=************************************************************************/
static void m__request_file_transfer (CLASS class, int source_number,
                                      int dest_number)
{
  char          dest_filename [MAX_FILENAME_LENGTH+1];
  char          source_filename [MAX_FILENAME_LENGTH+1];
  /*------------------------------------------------------------*/
  strcpy (source_filename, m__source_filename (m_transfer_count));
  strcpy (dest_filename, m__destination_filename (m_transfer_count));

  if (!m__create_random_file (source_filename, m_source_file_size))
    {
      printf ("<FATAL> Unable to create source file '%s'.\n",
	      source_filename);
      fflush (stdout);
      m__failure ("Unable to create source file.");
    }

  m__request_a_put (class, source_number, source_filename, 
                    dest_number, dest_filename);
  m_transfer_count ++;
}



/*=r=************************************************************************/
static void m__parse_and_execute_directive (char *dir)
     /* WHAT IT DOES:  Parses the given directive, and (if valid), 
      *   executes it.
      * NOTE:  Exits the program if the directive is not recognized.
      */
{
  char          arg1 [64];
  char          arg2 [64];
  char          arg3 [64];
  char          arg4 [64];
  char          arg5 [64];
  char          arg6 [64];
  char          arg7 [64];
  char          arg8 [64];
  char          arg9 [64];
  u_int_4       file_size;
  u_int_4       how_many;
  int           i;
  char          message [128];
  char          os_string [128];
  int           seconds;
  u_int_2       timeout;
  /*------------------------------------------------------------*/

  /* Separate the input directive into separate 'words' */
  strcpy (arg1, "\0");
  strcpy (arg2, "\0");
  strcpy (arg3, "\0");
  strcpy (arg4, "\0");
  strcpy (arg5, "\0");
  strcpy (arg6, "\0");
  strcpy (arg7, "\0");
  strcpy (arg8, "\0");
  strcpy (arg9, "\0");
  sscanf (dir, "%s %s %s %s %s %s %s %s %s", 
          arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
  m__convert_string_to_uppercase (arg1);

  if (m_node_count < 2)
    /* Make sure the user is using this program properly */
    {
      if ((strcmp (arg1, "HELP")) &&
          (strcmp (arg1, "EXIT")) &&
          (strcmp (arg1, "RUN")) &&
          (strcmp (arg1, "SYSTEM")) &&
          (strcmp (arg1, "NODE")))
        {
          printf ("<INPUT_ERROR> Must register 2 CFDP nodes!\n");
          printf ("(via the 'NODE' directive)\n");
          printf ("(example: 'node 23')\n");
          m__failure ("Must register 2 nodes at start of test");
        }
    }

  if (!strcmp (arg1, "HELP"))
    {
      m__help ();
      return;
    }

  else if (!strcmp (arg1, "EXIT"))
    {
      printf ("   Bye.\n");
      exit (1);
    }

  else if (!strcmp (arg1, "CLEAR_BETWEEN_TESTS"))
    /* Start fresh for next section of test */
    m__clear_between_test_runs ();

  else if (!strcmp (arg1, "GET"))
    /* Send one file from 'B' to 'A' */
    {
      m__request_file_transfer (CLASS_2, B, A);
      sleep (1);    /* Avoid race conditions */
    }

  else if (!strncmp (arg1, "GET*", 4))
    /* (One directive causes multiple 'gets') */
    {
      sscanf (arg1+4, "%lu", &how_many);
      if (how_many > 0)
        {
          printf ("   (Request for %lu 'gets')\n", how_many);
          for (i=0; i<how_many; i++)
            m__request_file_transfer (CLASS_2, B, A);
	  sleep (1);    /* Avoid race conditions */
        }
      else
        printf ("<SYNTAX_ERROR> (%s)\n", arg1);
    }

  else if (!strcmp (arg1, "GET_1"))
    /* A 'get' using Service Class 1 (rather than Service Class 2) */
    {
      m__request_file_transfer (CLASS_1, B, A);
      sleep (1);    /* Avoid race conditions */
    }

  else if (!strcmp (arg1, "GET_AND_PUT"))
    /* Send one file in each direction */
    {
      m__request_file_transfer (CLASS_2, B, A);
      m__request_file_transfer (CLASS_2, A, B);
      sleep (1);    /* Avoid race conditions */
    }

  else if (!strncmp (arg1, "GET_AND_PUT*", 12))
    /* (One directive causes multiple 'gets' and 'puts') */
    {
      sscanf (arg1+12, "%lu", &how_many);
      if (how_many > 0)
        {
          printf ("   (Request for %lu 'gets' and 'puts')\n", how_many);
          for (i=0; i<how_many; i++)
            {
              m__request_file_transfer (CLASS_2, B, A);
              m__request_file_transfer (CLASS_2, A, B);
            }
	  sleep (1);    /* Avoid race conditions */
        }
      else
        printf ("<SYNTAX_ERROR> (%s)\n", arg1);
    }

  else if (!strcmp (arg1, "LINK_SIM"))
    /* Directive for each CFDP node's Link Simulator; deliver to each node */
    {
      sprintf (message, "sim %s %s %s", arg2, arg3, arg4);
      for (i=0; i<m_node_count; i++)
        m__deliver_message_to_cfdp_node (i, message);
    }

  else if (!strcmp (arg1, "MIB"))
    /* Directive to set an MIB parameter for CFDP */
    {
      sprintf (message, "SET %s %s", arg2, arg3);
      for (i=0; i<m_node_count; i++)
        m__deliver_message_to_cfdp_node (i, message);
    }
      
  else if (!strcmp (arg1, "NODE"))
    {
      if (strlen(arg2) > 0)
        {
          if (!m__is_this_cfdp_node_registered (arg2))
            /* This is a new node, attempt to register it and open comm */
            {
              if (m__register_new_cfdp_node (arg2))
                printf ("   Registered new node '%s'.\n", arg2);
              else
                {
                  sprintf (message, "Unable to register CFDP node #%s", arg2);
                  m__failure (message);
                }
            }
        }
      else
        printf ("<SYNTAX_ERROR> no node ID given.\n");
    }

  else if (!strcmp (arg1, "PUT"))
    {
      m__request_file_transfer (CLASS_2, A, B);
      sleep (1);    /* Avoid race conditions */
    }

  else if (!strncmp (arg1, "PUT*", 4))
    /* (One directive causes multiple 'puts') */
    {
      sscanf (arg1+4, "%lu", &how_many);
      if (how_many > 0)
        {
          printf ("   (Request for %lu 'puts')\n", how_many);
          for (i=0; i<how_many; i++)
            m__request_file_transfer (CLASS_2, A, B);
	  sleep (1);    /* Avoid race conditions */
        }
      else
        printf ("<SYNTAX_ERROR> (%s)\n", arg1);
    }

  else if (!strcmp (arg1, "PUT_1"))
    {
      m__request_file_transfer (CLASS_1, A, B);
      sleep (1);    /* Avoid race conditions */
    }

  else if (!strcmp (arg1, "RUN"))
    {
      if (m_fp_for_input != stdin)
        m__failure ("Test scripts cannot be nested more than 2 levels");
      else if (strlen(arg2) == 0)
        m__failure ("<SCRIPT> No sub-script specified");
      else if ((m_fp_for_input = fopen (arg2, "r")) == NULL)
        {
          sprintf (message, "Unable to open the specified sub-script (%s)",
                  arg2);
          m__failure (message);
        }
      else
        {
          printf ("   Entering the sub-script '%s'...\n", arg2);
          /* Remember what line-number we are on (for our later return);
           * since we are entering a new script, the line number resets.
           */
          m_top_level_line_number = m_line_number;
          m_line_number = 0;
          strcpy (m_sub_script, arg2);
        }
    }

  else if (!strcmp (arg1, "SEND_TO_A"))
    /* Directive for first CFDP node; deliver it */
    {
      sprintf (message, "%s %s %s %s %s", arg2, arg3, arg4, arg5, arg6);
      m__deliver_message_to_cfdp_node (A, message);
    }

  else if (!strcmp (arg1, "SEND_TO_B"))
    /* Directive for second CFDP node; deliver it */
    {
      sprintf (message, "%s %s %s %s %s", arg2, arg3, arg4, arg5, arg6);
      m__deliver_message_to_cfdp_node (B, message);
    }

  else if (!strcmp (arg1, "SET_TIMEOUT"))
    {
      if (strlen(arg2) > 0)
        {
          sscanf (arg2, "%u", &timeout);
          if (timeout == 0)
            printf ("<INPUT_ERROR> Why is 'timeout' value zero?\n");
          else
            {
              m_timeout = timeout;
              printf ("   'Timeout' set to %u.\n", m_timeout);
            }
        }
      else
        printf ("<SYNTAX_ERROR> no 'timeout' value given.\n");
    }

  else if (!strcmp (arg1, "SOURCE_FILE_SIZE"))
    {
      if (strlen(arg2) > 0)
        {
          sscanf (arg2, "%lu", &file_size);
          if (file_size == 0)
            printf ("<INPUT_ERROR> Why is file-size parameter zero?\n");
          else
            {
              m_source_file_size = file_size;
              printf ("   Source file size set to %lu.\n", file_size);
            }
        }
      else
        printf ("<SYNTAX_ERROR> no 'source-file-size' value given.\n");
    }

  else if (!strcmp (arg1, "SYSTEM"))
    {
      sprintf (os_string, "%s %s %s %s %s %s %s %s", 
	       arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
      fflush (stdout);
      system (os_string);
    }

  else if (!strcmp (arg1, "VERIFY_FILE_TRANSFERS"))
    {
      printf ("   All trans complete; will now compare files...\n");
      if (!m__check_file_transfer())
        m__failure ("Unable to verify file transfer");
      printf ("   Success - all %u files transferred successfully.\n", 
              m_transfer_count);
    }

  else if (!strcmp (arg1, "VERIFY_CONDITION_CODE_AT_A"))
    /* Verify that the last completed transaction at node A had the
     * condition-code specified in arg2.
     */
    {
      if (!m__verify_condition_code (A, arg2))
	m__failure ("Unable to verify Condition-Code");
      else
	printf ("   Success (node A completed with proper Cond-Code)\n");
    }

  else if (!strcmp (arg1, "VERIFY_CONDITION_CODE_AT_B"))
    /* Verify that the last completed transaction at node A had the
     * condition-code specified in arg2.
     */
    {
      if (!m__verify_condition_code (B, arg2))
	m__failure ("Unable to verify Condition-Code");
      else
	printf ("   Success (node B completed with proper Cond-Code)\n");
    }

  else if (!strcmp (arg1, "VERIFY_CONDITION_CODE"))
    /* Verify that all nodes which had transactions have the specified
     * condition-code (presumably, all transactions have completed).
     */
    {
      for (i=0; i<m_node_count; i++)
	{
	  if (!m__verify_condition_code (i, arg2))
	    m__failure ("Unable to verify Condition-Code");
	}
      printf ("   Success (all nodes completed with proper Cond-Code)\n");
    }

  else if (!strcmp (arg1, "VERIFY_ABANDONED_AT_A"))
    /* Verify that at node A, the last completed transaction was abandoned */
    {
      if (m__verify_abandoned (A, "Yes"))
        printf ("   Success\n");
      else
        m__failure ("Unable to verify proper setting of 'Abandoned?'");
    }

  else if (!strcmp (arg1, "VERIFY_ABANDONED_AT_B"))
    /* Verify that at node A, the last completed transaction was abandoned */
    {
      if (m__verify_abandoned (B, "Yes"))
        printf ("   Success\n");
      else
        m__failure ("Unable to verify proper setting of 'Abandoned?'");
    }

  else if (!strcmp (arg1, "VERIFY_ABANDONED"))
    /* Verify that for all nodes, the last completed transaction was
     * abandoned (depending on value of arg2).
     */
    {
      for (i=0; i<m_node_count; i++)
	{
	  if (!m__verify_abandoned (i, arg2))
	    m__failure ("Unable to verify proper setting of 'Abandoned?'");
	}
      printf ("   Success (all nodes have proper 'Abandon' status).\n");
    }

  else if (!strcmp (arg1, "VERIFY_TRANSACTIONS_EXIST"))
    /* Verify that for all nodes, there is at least one active transaction */
    {
      for (i=0; i<m_node_count; i++)
	{
	  if (!m__verify_transactions_exist (i))
	    m__failure ("Unable to verify that transactions exist at "
			"all nodes");
	}
      printf ("   Success (all nodes have at least one transaction).\n");
    }

  else if (!strcmp (arg1, "WAIT"))
    /* A wait for a specific number of seconds */
    {
      sscanf (arg2, "%u", &seconds);
      printf ("  ");
      for (i=seconds; i>0; i--)
        {
          if ((i == seconds) || 
              (i < 10) || 
              (i % 5 == 0))
            {
              printf (" %u", i);
              fflush (stdout);
            }
          sleep (1);
        }
    }

  else if (!strcmp (arg1, "WAIT_FOR_TRANSACTION_CANCELLATION"))
    /* Wait for a transaction to be cancelled */
    {
      /* ^^^ sleep (1); */  /* avoid named-pipe problems  kludge!!! */
      if (!m__wait_for_trans_cancellation (m_timeout))
	m__failure ("Unable to verify transaction cancellation.");
      printf ("   A transaction is being cancelled.\n");
    }

  else if (!strcmp (arg1, "WAIT_FOR_TRANSACTION_COMPLETION"))
    /* Wait for all active transactions to complete */
    {
      sleep (1);   /* Avoid a race-condition */
      if (!m__wait_for_trans_completion (m_timeout))
        m__failure ("Unable to verify transaction completion.");
      printf ("   All transactions have completed.\n");
    }

  else
    {
      printf ("Unrecognized directive (%s).\n", arg1);
      m__help ();
      m__failure ("Unrecognized directive");
    }
}



/*=r=************************************************************************/
static boolean m__read_input_line (FILE *fp, char *line)
     /* WHAT IT DOES:  Attempts to read one line from the given file-pointer; 
      *   returns 1 if successful, 0 otherwise.  The returned line will not 
      *   contain a newline char; it can be up to 'MAX_LINE_LENGTH' chars.
      */
{
  /*------------------------------------------------------------*/

  /* Attempt to read a line from the specified file */
  fgets (line, MAX_LINE_LENGTH, fp);
  if (feof(fp))
    return (0);

  /* Ensure that the string 'terminates' */
  line[MAX_LINE_LENGTH-1] = STRING_TERMINATOR;

  /* Remove any trailing 'newline' character */
  if (line[strlen(line)-1] == '\n')
    line[strlen(line)-1] = STRING_TERMINATOR;

  return (1);
}



/*=r=*************************************************************************/
void m__sigpipe_handler (int signal)
     /* WHAT IT DOES:  ALlows us to be aware of a lost pipe.  (Exits). */
{
  char           msg [128];
  /*------------------------------------------------------------*/
  
  strcpy (msg, "<FATAL> SIGPIPE signal received.\n");
  printf ("%s", msg);
  fflush (stdout);
  m__failure ("SIGPIPE");
}




/*=r=************************************************************************/
int main (int argc, char *argv[])
{
  char                  filename [MAX_FILENAME_LENGTH];
  char                  line [MAX_LINE_LENGTH];
  struct sigaction      new_action;
  struct sigaction      old_action;
  /*------------------------------------------------------------*/

  printf ("Test_cfdp: Version %s.\n", INTERNAL_VERSION);

  /* Give help if desired/needed */
  if (argc >= 2)
    {
      m__help ();
      exit (1);
    }

  /* Register SIGPIPE signal-handler */
  sigemptyset (&new_action.sa_mask);
  new_action.sa_flags = 0;
  new_action.sa_handler = m__sigpipe_handler;
  if (sigaction (SIGPIPE, &new_action, &old_action) != 0)
    {
      printf ("<FATAL> Unable to register SIGPIPE signal-handler.\n");
      exit (1);
    }

  /* The top-level 'script' is read from stdin */
  m_fp_for_input = stdin;
  memset (m_sub_script, 0, sizeof(m_sub_script));

  /* Delete any leftover source/destination files from previous runs
   * (otherwise, they can distort the results)
   */
  sprintf (filename, "%s*%s", FILENAME_PREFIX_FOR_SOURCE,
           FILENAME_SUFFIX_FOR_SOURCE);
  m__delete_file (filename);
  sprintf (filename, "%s*%s", FILENAME_PREFIX_FOR_DESTINATION,
           FILENAME_SUFFIX_FOR_DESTINATION);
  m__delete_file (filename);

  /*---------------------------------------------------------------*/
  /* Read, parse, and (possibly) execute each input line until EOF */
  /*---------------------------------------------------------------*/
  for (;;)
    {
      if (!m__read_input_line (m_fp_for_input, line))
        /* There is no more input from the current file-pointer... */
        {
          if (m_fp_for_input == stdin)
            /* The entire test is complete */
            {
              printf ("   Test result:  ***Passed***\n");
              exit (1);
            }
          else
            /* A sub-script has completed; return to top-level */
            {
              printf ("   Sub-script '%s' completed; back to top-level...\n",
                      m_sub_script);
              memset (m_sub_script, 0, sizeof(m_sub_script));
              fclose (m_fp_for_input);
              m_fp_for_input = stdin;
              /* Restore the line-number to the branching-off point */
              m_line_number = m_top_level_line_number;
            }
        }
      printf ("\n> %s\n", line);    fflush (stdout);
      m_line_number ++;
      m__remove_any_comment (line, COMMENT_STARTS_WITH_THIS_CHAR);
      m__remove_trailing_whitespace (line);
      if (strlen(line) > 0)
        m__parse_and_execute_directive (line);
      fflush (stdout);
    }

  return (1);
}

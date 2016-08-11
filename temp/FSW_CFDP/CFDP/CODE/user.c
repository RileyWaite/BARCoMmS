/* FILE: user.c
 * VERSION: 2.3k 2004_09_20
 * SPECS:  See user.h.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include "cfdp_code.h"

static boolean           m_are_pipes_enabled = NO;
static boolean           m_debug = NO;
static boolean           m_debug_pipe = NO;
static FILE             *m_fp_in = NULL;
static FILE             *m_fp_out = NULL;
static boolean           m_was_last_trans_abandoned = NO;



/*=r=************************************************************************/
void indication (INDICATION_TYPE type, TRANS_STATUS info){
    char                  string1 [1024];
    char                  string2 [1024];
    char                  substring [1024];
    /*------------------------------------------------------------*/

    /* A state machine has been allocated to handle a new transaction */
    if (type == IND_MACHINE_ALLOCATED){
    /* Add this transaction to our list */
    trans_list__add_trans (info.trans);
    /* Display a message */
    if ((info.role == CLASS_1_SENDER) || (info.role == CLASS_2_SENDER))
        sprintf (substring, "sending '%s' -> '%s'", info.md.source_file_name, info.md.dest_file_name);
    else if ((info.role == CLASS_1_RECEIVER) || (info.role == CLASS_2_RECEIVER))
    {
        if (info.has_md_been_received){
            sprintf (substring, "receiving '%s' <- '%s'", info.md.dest_file_name, info.md.source_file_name);
        }
        else{
            sprintf (substring, "receiving; file name not yet known");
        }
    }
    else{
        sprintf (substring, "<PROBLEM> unrecognized role");
    }

    msg__ (">>> Transaction %s started (%s)...\n", cfdp_trans_as_string (info.trans), substring);

    transStatus = 0;
    }


    /* A state machine has been deallocated (transaction completed) */
    else if (type == IND_MACHINE_DEALLOCATED){
        /* Remove this transaction from our list */
        trans_list__remove_trans (info.trans);

        /* This is our new 'last transaction completed', so update
        * internal status used for automated testing.
        */
        m_was_last_trans_abandoned = info.abandoned;

        /* Display a message */

        sprintf (string1, ">>> Transaction %s (%s -> %s): ",
        cfdp_trans_as_string (info.trans),
        info.md.source_file_name, info.md.dest_file_name);

        if (info.final_status == FINAL_STATUS_SUCCESSFUL){
            sprintf (string2, "successful");
            transStatus = 1;
        }
        else if (info.final_status == FINAL_STATUS_ABANDONED){
            if (info.condition_code == NO_ERROR){
                sprintf (string2, "abandoned (User Request)");
            }
            else{
                sprintf (string2, "abandoned (%s)", cfdp_condition_as_string (info.condition_code));
            }
            transStatus = 2;
        }
        else if (info.final_status == FINAL_STATUS_CANCELLED){
            sprintf (string2, "cancelled (%s)", cfdp_condition_as_string (info.condition_code));
            transStatus = 3;
        }
        else if (info.final_status == FINAL_STATUS_NO_METADATA){
            sprintf (string2, "failed (Metadata not received)");
            transStatus = 4;
        }
        else if (info.final_status == FINAL_STATUS_UNKNOWN){
            sprintf (string2, "<PROBLEM> Final Status = Unknown");
            transStatus = 5;
        }
        else{
            sprintf (string2, "<PROBLEM> Final Status unrecognized");
            transStatus = 6;
        }

        msg__ ("%s%s\n\n", string1, string2);
    }
}



/*=r=************************************************************************/
static char *m__what_is_my_input_filename (void)
     /* WHAT IT DOES:  Generates (and returns) the name of the file that 
      *   my program uses for input.
      * NOTE:  Each CFDP node has its own (unique) filename.
      */
{
  static char         filename [128];
  char                my_id_as_string [MAX_MIB_VALUE_LENGTH];
  /*------------------------------------------------------------*/
  strcpy (filename, "cfdp_");
  cfdp_get_mib_parameter (MIB_MY_ID, my_id_as_string);
  strcat (filename, my_id_as_string);
  strcat (filename, ".in");
  return (filename);
}



/*=r=************************************************************************/
static char *m__what_is_my_output_filename (void)
     /* WHAT IT DOES:  Generates (and returns) the name of the file that 
      *   my program uses for output.
      * NOTE:  Each CFDP node has its own (unique) filename.
      */
{
  static char         filename [128];
  char                my_id_as_string [MAX_MIB_VALUE_LENGTH];
  /*------------------------------------------------------------*/
  strcpy (filename, "cfdp_");
  cfdp_get_mib_parameter (MIB_MY_ID, my_id_as_string);
  strcat (filename, my_id_as_string);
  strcat (filename, ".out");
  return (filename);
}



/*=r=************************************************************************/
static void m__create_and_open_input_pipe (void)
     /* WHAT IT DOES:  Creates an input file (pipe) for this program.
      * NOTE:  Each CFDP node has its own unique input file-name.
      */
   {
     char                  filename [128];
     int                   status_of_create_pipe;
   /*------------------------------------------------------------*/
     strcpy (filename, m__what_is_my_input_filename());

     msg__ ("Creating my input pipe (%s)... ", filename);
     fflush (stdout);
     status_of_create_pipe = mkfifo (filename, S_IFIFO | 0755);
     if (status_of_create_pipe == 0)
       msg__ ("done (fresh start).\n");
     else if (errno == EEXIST)
       msg__ ("done (pipe already exists).\n");
     else
       {
         msg__ ("\n<FAILURE>  Unable to create my input pipe.\n");
         exit (1);
       }

     msg__ ("Opening my input pipe... ");
     fflush (stdout);
     if ((m_fp_in = fopen (filename, "r")) == NULL)
       {
         msg__ ("\n<FAILURE> Unable to open my input pipe.\n");
         exit (1);
       }
     msg__ ("done.\n");
   }



/*=r=************************************************************************/
static void m__create_and_open_output_pipe (void)
     /* WHAT IT DOES:  Creates an output file (pipe) for this program.
      * NOTE:  Each CFDP node has its own unique output file-name.
      */
   {
     char                  filename [128];
     int                   status_of_create_pipe;
   /*------------------------------------------------------------*/
     strcpy (filename, m__what_is_my_output_filename());

     msg__ ("Creating my output pipe (%s)... ", filename);
     fflush (stdout);
     status_of_create_pipe = mkfifo (filename, S_IFIFO | 0755);
     if (status_of_create_pipe == 0)
       msg__ ("done (fresh start).\n");
     else if (errno == EEXIST)
       msg__ ("done (pipe already exists).\n");
     else
       {
         msg__ ("\n<FAILURE>  Unable to create my output pipe.\n");
         exit (1);
       }

     msg__ ("Opening my output pipe... ");
     fflush (stdout);
     if ((m_fp_out = fopen (filename, "w")) == NULL)
       {
         msg__ ("\n<FAILURE> Unable to open my output pipe.\n");
         exit (1);
       }
     msg__ ("done.\n");
   }



/*=r=************************************************************************/
static boolean m__is_there_input_from_this_fd (int fd_to_check)
/* WHAT IT DOES:  Returns immediately.  Indicates whether or not a message is
 *   available via the specified file-descriptor.  (Does not read the message).
 * WARNING:  The 'message' may be an EOF.
 * WARNING:  Will exit this program if the 'select' call fails.
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
     FD_SET (fd_to_check, &fdvar);
     ready_count = select (fd_to_check+1, &fdvar, (fd_set *) 0, 
                           (fd_set *) 0, &timeout);
     if (ready_count < 0)
       {
         msg__ ("<FATAL> 'Select' call failed.\n");
         exit (1);
       }
     else if (ready_count == 0)
       /* Timeout */
       ;
     else if (FD_ISSET (fd_to_check, &fdvar))
       is_msg_waiting = YES;
     else
       /* No msg */
       ;

     return (is_msg_waiting);
   }



/*=r=************************************************************************/
static boolean m__intercept_secret_commands (char *user_input)
#define MAX_ANSWER_LENGTH 80
{
  u_int_4          active_count;
  char             answer [MAX_ANSWER_LENGTH+1];
  char             arg1 [64];
  char             arg2 [64];
  char             arg3 [64];
  char             arg4 [64];
  CONDITION_CODE   code;
  int              i;
  u_int_4          number;
  boolean          secret = NO;
  SUMMARY_STATUS   summary;
  /*------------------------------------------------------------*/

  /* Extract all args (tokens) from the given input, and convert
   * some of them to lowercase.
   */
  memset (arg1, 0, sizeof(arg1));
  memset (arg2, 0, sizeof(arg2));
  memset (arg3, 0, sizeof(arg3));
  memset (arg4, 0, sizeof(arg4));
  sscanf (user_input, "%64s %64s %64s %64s", arg1, arg2, arg3, arg4);
  for (i=0; i<strlen(arg1); i++)
    arg1[i] = tolower(arg1[i]);
  for (i=0; i<strlen(arg2); i++)
    arg2[i] = tolower(arg2[i]);
  
  if ((!strcmp (arg1, "use_pipes")) ||
      (!strcmp (arg1, "p")))
    {
      secret = YES;
      if (!m_are_pipes_enabled)
        {
          m__create_and_open_output_pipe ();
          m__create_and_open_input_pipe ();
        }
      m_are_pipes_enabled = YES;
    }

  else if (!strcmp (arg1, "how_many_active_transactions?"))
    {
      secret = YES;
      summary = cfdp_summary_status ();
      active_count = summary.how_many_senders + summary.how_many_receivers;
      sprintf (answer, "%lu", active_count);
      ASSERT__ (strlen(answer) <= MAX_ANSWER_LENGTH);
      if (m_debug_pipe)
        msg__ ("Pipe output: %s\n", answer);
      /* ^^^ sleep (1);*/   /* Kludge!!!   Needed for back-to-back msgs to named-pipe */
      fprintf (m_fp_out, "%s\n", answer);
      fflush (m_fp_out);
    }

  else if (!strcmp (arg1, "last_condition_code?"))
    {
      secret = YES;
      code = cfdp_last_condition_code();
      if (code == NO_ERROR)
        strcpy (answer, "No_error");
      else if (code == CANCEL_REQUEST_RECEIVED)
        strcpy (answer, "Cancel_request_received");
      else if (code == POSITIVE_ACK_LIMIT_REACHED)
        strcpy (answer, "Positive_ack_limit_reached");
      else if (code == NAK_LIMIT_REACHED)
        strcpy (answer, "Nak_limit_reached");
      else if (code == INACTIVITY_DETECTED)
        strcpy (answer, "Inactivity_detected");
      else if (code == FILESTORE_REJECTION)
        strcpy (answer, "Filestore_rejection");
      else if (code == FILE_CHECKSUM_FAILURE)
	strcpy (answer, "File_checksum_failure");
      else if (code == FILE_SIZE_ERROR)
	strcpy (answer, "File_size_error");
      else 
        strcpy (answer, "?");
      if (m_debug_pipe)
        msg__ ("Pipe output: %s\n", answer);
      /* ^^^ sleep (1);*/   /* Kludge!!!   Needed for back-to-back msgs to named-pipe */
      fprintf (m_fp_out, "%s\n", answer);
      fflush (m_fp_out);
    }

  else if (!strcmp (arg1, "cancelling?"))
    {
      secret = YES;
      if (cfdp_is_a_trans_being_cancelled ())
	strcpy (answer, "Yes");
      else
	strcpy (answer, "No");
      if (m_debug_pipe)
        msg__ ("Pipe output: %s\n", answer);
      /* ^^^ sleep (1);*/   /* Kludge!!!   Needed for back-to-back msgs to named-pipe */
      fprintf (m_fp_out, "%s\n", answer);
      fflush (m_fp_out);
    }

  else if (!strcmp (arg1, "last_transaction_abandoned?"))
    {
      secret = YES;
      if (m_was_last_trans_abandoned)
	strcpy (answer, "Yes");
      else
	strcpy (answer, "No");
      if (m_debug_pipe)
        msg__ ("Pipe output: %s\n", answer);
      /* ^^^ sleep (1);*/   /* Kludge!!!   Needed for back-to-back msgs to named-pipe */
      fprintf (m_fp_out, "%s\n", answer);
      fflush (m_fp_out);
    }

  else if (!strcmp (arg1, "date"))
    {
      secret = YES;
      system ("date");
    }

  else if (!strcmp (arg1, "print"))
    {
      secret = YES;
      msg__ ("\n\n\n%s %s %s\n", arg2, arg3, arg4);
    }

  else if (!strcmp (arg1, "set_trans_seq_num"))
    {
      secret = YES;
      number = atoi (arg2);
      cfdp_set_trans_seq_num (number);
      msg__ ("Trans_seq_num set to %lu.\n", number);
    }

  return (secret);
}
#undef MAX_ANSWER_LENGTH



/*=r=*************************************************************************/
static void m__read_unbuffered_line (int fd, char *line)
{
  char             current;
  boolean          end_of_file;
  int              line_length;
  int              status;
  /*------------------------------------------------------------*/

  end_of_file = NO;
  line_length = 0;
  current = '?';
  line[0] = '\0';

  while ((current != '\n') && !end_of_file)
    {
      status = read (fd, &current, 1);
      if (status == -1)
	{
	  msg__ ("<FATAL> 'read' failed in m__read_unbuffered_line.\n");
	  exit (1);
	}
      else if (status == 0)
	end_of_file = YES;
      else
	/* Append this char to the line */
	{
	  line[line_length] = current;
	  line_length ++;
	  line[line_length] = '\0';
	}
    }

  if (m_debug_pipe)
    msg__ ("Pipe input: %s", line);
}



/*=r=************************************************************************/
static void m__read_user_input (FILE *fp, char *user_input)
#define  MAX_USER_INPUT_LENGTH  128
{
  static int        input_empty_count = 0;
  static int        split_message_count = 0;
  /*------------------------------------------------------------*/
  
  if (fgets (user_input, MAX_USER_INPUT_LENGTH, fp) == NULL)
    {
      system ("date");
      if (fp == stdin)
	{
	  if (feof (stdin))
	    {
          msg__ ("^^^ EOF from stdin.\n");
	      strcpy (user_input, " ");
	      return;
	    }
	  else
	    {
          msg__ ("^^^ fgets failed (stdin).\n");
          msg__ ("^^^ Bye.\n");
	      exit (1);
	    }
	}

      else  /* named-pipe fgets failure */
	{
	  if (feof (fp))
	    {
          msg__ ("^^^ EOF from named-pipe.\n");
	      strcpy (user_input, " ");
	      return;
	    }
	  else
	    {
          msg__ ("^^^ fgets failed (named-pipe).\n");
          msg__ ("^^^ Bye.\n");
	      exit (1);
	    }
	}
    }

  if (m_debug && (strlen(user_input) > 0))
    {
      if (fp == stdin)
        msg__ ("CFDP User input: %s", user_input);
      else if (m_debug_pipe)
        msg__ ("Pipe input: %s", user_input);
    }

  /* Try to detect and report if the named-pipe splits a message */
  if (strlen(user_input) == 0)
    {
      input_empty_count ++;
      if (input_empty_count <= 50)
	{
	  system ("date");
      msg__ ("^^^ m__read_user_input:  string length is zero!\n");
	  fflush (stdout);
	}
      return;
    }
  else if (user_input[strlen(user_input)-1] != '\n')
    {
      split_message_count ++;
      if (split_message_count <= 50)
	{
	  system ("date");
      msg__ ("^^^ m__read_user_input:  "
		  "string does not end with newline!\n");
      msg__ ("^^^ string = '%s'.\n", user_input);
	  fflush (stdout);
	}
    }
}
#undef MAX_USER_INPUT_LENGTH



/*=r=************************************************************************/
boolean user_input__poll (char *user_input)
     /* Note:  on 2007_06_21, enhanced to alternate which input source
      *   gets checked first.    I was afraid that Pipes were getting 
      *   locked out.
      */
   {
     static boolean    eof_from_pipe = NO;
     static boolean    eof_from_stdin = NO;
     int               fd;
   /*------------------------------------------------------------*/

     /* Check stdin first */
     if (!eof_from_stdin)
       {
	 if (m__is_there_input_from_this_fd (STDIN_FILENO))
	   {
	     m__read_user_input (stdin, user_input);
	     if (feof (stdin))
	       {
         msg__ ("user_input__poll:  "
			 "EOF (stdin); no further reads\n");
		 eof_from_stdin = YES;
	       }
	     else if (!m__intercept_secret_commands (user_input))
	       return (YES);
	   }
       }
     
     /* Then, check named-pipe */
     if (m_are_pipes_enabled)
       {
	 if (!eof_from_pipe)
	   {
	     fd = fileno (m_fp_in);
	     if (m__is_there_input_from_this_fd (fd))
	       {
		 if (m_debug_pipe)
		   {
             msg__ ("^^^ Got message from tester.\n");
		     fflush (stdout);
		   }
		 /* Acknowledge this input */
		 fprintf (m_fp_out, ".\n");  fflush (m_fp_out);
		 if (m_debug_pipe)
		   {
             msg__ ("^^^ Ack'd message from tester.\n");
		     fflush (stdout);
		   }
		 /* Read and execute the input */
		 m__read_unbuffered_line (fd, user_input);
		 if (feof (m_fp_in))
		   {
             msg__ ("user_input__poll:  "
			     "EOF (pipe); no further reads\n");
		     eof_from_pipe = YES;
		   }
		 else if (!m__intercept_secret_commands (user_input))
		   return (YES);
	       }
	   }
       }

     if (eof_from_stdin && eof_from_pipe)
       {
     msg__ ("^^^ user_input__poll:  Both sources have given EOF.\n");
     msg__ ("Bye.\n");
	 exit (1);
       }

     return (NO);
   }

/*=r=************************************************************************/
void msg__ (const char *format, ...)
{
  va_list         arg_ptr;
  /*------------------------------------------------------------*/
  va_start (arg_ptr, format);
  vprintf (format, arg_ptr);
  va_end (arg_ptr);
}

/*=r=************************************************************************/
void d_msg__ (const char *format, ...)
{
    va_list         arg_ptr;
    /*------------------------------------------------------------*/
    va_start (arg_ptr, format);
    vprintf (format, arg_ptr);
    va_end (arg_ptr);
}

/*=r=************************************************************************/
void i_msg__ (const char *format, ...)
{
    va_list         arg_ptr;
    /*------------------------------------------------------------*/
    va_start (arg_ptr, format);
    vprintf (format, arg_ptr);
    va_end (arg_ptr);
}

/*=r=************************************************************************/
void w_msg__ (const char *format, ...)
{
    va_list         arg_ptr;
    /*------------------------------------------------------------*/
    va_start (arg_ptr, format);
    vprintf (format, arg_ptr);
    va_end (arg_ptr);
}

/*=r=************************************************************************/
void e_msg__ (const char *format, ...)
{
    va_list         arg_ptr;
    /*------------------------------------------------------------*/
    va_start (arg_ptr, format);
    vprintf (format, arg_ptr);
    va_end (arg_ptr);
}

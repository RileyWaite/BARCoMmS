/* FILE: cfdp.c -- main program for a CFDP application.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */
#define PROGRAM_VERSION "2007_06_08"

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <signal.h>
#include "cfdp_code.h"
#include "time.h"

#define DEFAULT_CFDP_NODE_AS_STRING "23"
#define  NO  0
#define  YES  1


static int           m_cycles_between_updates = 200;
static boolean       m_periodic_status = NO;




/*=r=*************************************************************************/
int printf_noop (const char *input, ...)
     /* WHAT IT DOES:  This routine looks like printf but does nothing. */
{
  /*------------------------------------------------------------*/

  ; /* Do nothing */
  return (0);
}



/*=r=************************************************************************/
static void m__give_help_and_exit (void)
     /* WHAT IT DOES:  Gives some help about how to start this program, 
      *   then exits.
      */
   {
   /*------------------------------------------------------------*/
     msg__ ("\n************************* Help *************************\n"
            "   USAGE:  cfdp <id>\n"
            "   EXAMPLE:  cfdp 23\n"
            "   (Requests are entered as [src_file] [dest_id] [dest_file]\n"
            "   (Defaults are 'cfdp.in', '24', 'cfdp.out')\n"
	    "   (To test engine robustness, enter 'cfdp -r')\n"
            "************************* Help *************************\n\n");
     exit (1);
   }



/*=r=*************************************************************************/
static void m__give_detailed_help (void)
     /* WHAT IT DOES:  Gives help about the commands that are accepted 
      *   by this program.
      * NOTE:  The module 'user.c' intercepts some user input 
      *   (look for 'secret' in user.c), so be careful about choosing
      *   the syntax of new directives.
      */
{
  /*------------------------------------------------------------*/

  msg__ ("\n********** Available Commands  **********\n"
	 "   To disable engine messages:     di[sable_messages]\n"
	 "   To enable engine messages:      en[able_messages]\n"
	 "   Get MIB parameter example:      get ack_limit\n"
	 "   To see a list of transactions:  l[ist]\n"
	 "   To see MIB as string:           mib\n"
	 "   To toggle periodic status:      n\n"
         "   To reset statistical totals:    reset_totals\n"
	 "   To test engine robustness:      robust?\n"
	 "   Set MIB parameter example:      set ack_limit 10\n"
	 "   Link Simulator example:         sim success_rate=90\n"
	 "   To see summary engine status:   sum[mary]\n"
	 "   To see trans status once:       v\n"
	 "   To see detailed status          detailed_status ____\n"
	 "                      e.g. detailed_status 23_1\n"
	 "   To set cycles between updates:  update ___\n"
	 "   (50 == sim success_rate=50)   etc\n"
	 "   (p1 == put cfdp_flight 24 88)\n"
	 "   (p2 == put cfdp_ground 24 89\n"
	 "\n"
	 );
}



/*=r=************************************************************************/
static void m__show_config (void)
     /* WHAT IT DOES:  Outputs messages that show the program's config */
{
  /*------------------------------------------------------------*/
#if IS_DYNAMIC_ALLOCATION_ENABLED==0
  msg__ ("(static allocation only)\n");
  msg__ ("   MAX_CONCURRENT_TRANSACTIONS=%u.\n", MAX_CONCURRENT_TRANSACTIONS);
  msg__ ("   MAX_GAPS_PER_TRANSACTION=%u.\n", MAX_GAPS_PER_TRANSACTION);

#elif IS_DYNAMIC_ALLOCATION_ENABLED==1
  msg__ ("(dynamic allocation enabled)\n");

#else
#error Enable or disable dynamic memory allocation in 'memory_use.h'.
#endif

  msg__ ("   MAX_FILE_CHUNK_SIZE=%u\n", MAX_FILE_CHUNK_SIZE);
  msg__ ("   MAX_PDU_LENGTH=%u.\n", MAX_PDU_LENGTH);
  msg__ ("   MAX_DATA_LENGTH=%u.\n", MAX_DATA_LENGTH);
  msg__ ("   Uses %lu bytes per open transaction.\n", 
         cfdp_memory_use_per_trans ());
}



/*=r=*************************************************************************/
static void m__show_trans_details (char *trans_as_string)
     /* WHAT IT DOES:  Shows the detailed status for the specified transaction.
      * INPUT:  The transaction-id represented as a char-string.
      */
{
  u_int_4              bytes_transferred;
  u_int_4              file_size;
  u_int_4              secs_left;
  TRANS_STATUS         status;
  char                 string [1000];
  TIMER_TYPE           timer_type;
  struct tm           *tm_ptr;
  TRANSACTION          trans;
  /*------------------------------------------------------------*/

  printf ("\n Showing detailed status of transaction: %s.\n", 
	  trans_as_string);

  if (!cfdp_trans_from_string (trans_as_string, &trans))
    {
      printf ("m__show_trans_details:  conversion of string to "
	      "trans-id failed.\n");
      return;
    }

  if (!cfdp_transaction_status (trans, &status))
    {
      printf ("Call to 'cfdp_transaction_status' failed.\n");
      return;
    }
  
  tm_ptr = localtime (&status.start_time);
  printf ("When did this trans start?  %s", asctime (tm_ptr));

  printf ("Which CFDP entity is our partner?  %s\n",
	  cfdp_id_as_string (status.partner_id));

  printf ("What is our role?  %s\n",
	  cfdp_role_as_string (status.role));

  printf ("What file (if any) is being transferred?  ");
  if (status.md.file_transfer)
    printf ("%s -> %s\n",
	    status.md.source_file_name, status.md.dest_file_name);
  else
    printf ("none.\n");

  if (status.md.file_transfer)
    {
      if (!cfdp_transaction_progress (trans, &bytes_transferred, &file_size))
	printf ("<ERROR> Call to 'cfdp_transaction_progress' failed.\n");
      else
	printf ("How big is the file, and how many bytes xferred so far?\n"
		"   %lu of %lu bytes have been transferred.\n",
		bytes_transferred, file_size);

      if (!cfdp_transaction_gaps_as_string (trans, string, sizeof(string)))
	printf ("<ERROR> Call to 'cfdp_transaction_gaps_as_string failed.\n");
      else
	printf ("What file-data is still missing?  %s\n", string);
    }

  printf ("Is this trans currently frozen?  ");
  if (status.frozen)
    printf ("yes\n");
  else
    printf ("no\n");

  printf ("Is this trans currently suspended?  ");
  if (status.suspended)
    printf ("yes\n");
  else
    printf ("no\n");

  printf ("Which timer is currently running, and how many seconds left?\n");
  if (!cfdp_transaction_timer_status (trans, &timer_type, &secs_left))
    printf ("<ERROR> Call to 'cfdp_transaction_timer_status' failed.\n");
  else
    {
      if (timer_type == NO_TIMER)
	printf ("   No timer is running.\n");
      else if (timer_type == ACK_TIMER)
	printf ("   Ack-timer has %lu seconds left.\n", secs_left);
      else if (timer_type == NAK_TIMER)
	printf ("   Nak-timer has %lu seconds left.\n", secs_left);
      else if (timer_type == INACTIVITY_TIMER)
	printf ("   Inactivity-timer has %lu seconds left.\n", secs_left);
      else
	printf ("   <ERROR> Undefined timer_type\n");
    }

  printf ("Has this trans been cancelled?  ");
  if (status.cancelled)
    printf ("yes\n");
  else
    printf ("no\n");

  printf ("Has this trans finished?  ");
  if (status.finished)
    printf ("yes\n");
  else
    printf ("no\n");

  if (status.finished)
    {
      printf ("What is the final status?  ");
      if (status.final_status == FINAL_STATUS_UNKNOWN)
	printf ("unknown");
      else if (status.final_status == FINAL_STATUS_SUCCESSFUL)
	printf ("successful");
      else if (status.final_status == FINAL_STATUS_CANCELLED)
	printf ("cancelled");
      else if (status.final_status == FINAL_STATUS_ABANDONED)
	printf ("abandoned");
      else if (status.final_status == FINAL_STATUS_NO_METADATA)
	printf ("no Metadata received");
      else
	printf ("<ERROR> unrecognized final-status value.\n");

      if (status.cancelled)
	printf ("What is the Condition-Code (why was it cancelled)?  %s\n",
		cfdp_condition_as_string (status.condition_code));
    }

  printf ("\n");
}



/*=r=*************************************************************************/
static void m__show_transactions_status (void)
     /* WHAT IT DOES:  Shows the detailed status of each in-progress 
      *   transaction.
      */
{
  boolean              am_i_sender;
  u_int_4              bytes_transferred;
  char                 cancelled_string [1024];
  char                 dest_file [MAX_FILE_NAME_LENGTH+1];
  u_int_4              file_size;
  char                 frozen_string [1024];
  char                 gaps_string [60];
  struct tm           *local_time_ptr;
  int                  percentage;
  ROLE                 role;
  char                 src_file [MAX_FILE_NAME_LENGTH+1];
  char                 suspended_string [1024];
  TRANSACTION          t;
  char                 start_time_string [128];
  char                 timer_string [1024];
  TIMER_TYPE           timer_type;
  u_int_4              timer_value;
  TRANS_STATUS         trans_status;
  /*------------------------------------------------------------*/

  msg__ ("\n");

  trans_list__open_walk ();
  while (trans_list__get_next (&t))
    {

      /*-------------------------------------*/
      /* Collect info about this transaction */
      /*-------------------------------------*/

      /* Get the generic public status of this transaction... */
      if (!cfdp_transaction_status (t, &trans_status))
	msg__ ("<ERROR> call to cfdp_transaction_status failed.\n");

      /* ... and assemble it nicely */

      role = trans_status.role;
      if ((role == CLASS_1_SENDER) || (role == CLASS_2_SENDER))
	am_i_sender = YES;
      else
	am_i_sender = NO;

      if ((am_i_sender) || (trans_status.has_md_been_received))
	{
	  strcpy (src_file, trans_status.md.source_file_name);
	  strcpy (dest_file, trans_status.md.dest_file_name);
	}
      else
	{
	  strcpy (src_file, "?");
	  strcpy (dest_file, "?");
	}

      strcpy (frozen_string, "");
      if (trans_status.frozen)
	strcpy (frozen_string, "frozen");

      strcpy (suspended_string, "");
      if (trans_status.suspended)
	strcpy (suspended_string, "suspended");
      
      strcpy (cancelled_string, "");
      if (trans_status.cancelled)
	strcpy (cancelled_string, "cancelled");

      /* Get transaction-progress info */
      bytes_transferred = file_size = 0;
      if (!cfdp_transaction_progress (t, &bytes_transferred, &file_size))
	msg__ ("<PROBLEM> call to cfdp_transaction_progress failed.\n");
      if (file_size == 0)
	percentage = 0;
      else
	percentage = (bytes_transferred * 100) / file_size;

      /* Get timer info... */
      if (!cfdp_transaction_timer_status (t, &timer_type, &timer_value))
	msg__ ("<PROBLEM> call to cfdp_transaction_timer_status failed.\n");

      /* ... and assemble it nicely */
      if (timer_type == NO_TIMER)
	strcpy (timer_string, "no timer running");
      else if (timer_type == ACK_TIMER)
	sprintf (timer_string, "ack-timer@%lu (#%lu)", 
		 timer_value, trans_status.attempts);
      else if (timer_type == NAK_TIMER)
	sprintf (timer_string, "nak-timer@%lu (#%lu)", 
		 timer_value, trans_status.attempts);
      else if (timer_type == INACTIVITY_TIMER)
	sprintf (timer_string, "inactivity-timer@%lu", 
		 timer_value);
      else
	msg__ ("<PROBLEM> timer_type not recognized.\n");

      /* Get a list of filedata gaps (formatted as a char-string) */
      if (!cfdp_transaction_gaps_as_string (t, gaps_string, 
					    sizeof(gaps_string)))
	msg__ ("<PROBLEM> call to cfdp_transaction_gaps_as_string failed.\n");

      /* Convert start-time to char-string */

      local_time_ptr = localtime (&trans_status.start_time);
      strftime (start_time_string, 128, "%H:%M", local_time_ptr);

      /*-----------------*/
      /* Output the info */
      /*-----------------*/

      msg__ ("%s:  %s  %s -> %s  started: %s\n",
	     cfdp_trans_as_string (t),
	     cfdp_role_as_string (trans_status.role),
	     src_file,
	     dest_file,
	     start_time_string);

      msg__ ("     phase-%u   %u%%   %u-naks   %s   %s %s %s\n",
	     trans_status.phase,
	     percentage,
	     trans_status.how_many_naks,
	     timer_string,
	     frozen_string,
	     cancelled_string,
	     suspended_string);
	     
      if (!am_i_sender)
	msg__ ("        gaps: %s.\n", gaps_string);
    }

  msg__ ("\n");
}



/*=r=*************************************************************************/
static void m__show_list_of_transactions (void)
     /* WHAT IT DOES:  Shows a list of the in-progress transactions. */
{
  int                  count;
  TRANSACTION          t;
  /*------------------------------------------------------------*/

  msg__ ("\nList of transactions:\n");

  count = 0;
  trans_list__open_walk ();
  while (trans_list__get_next (&t))
    {
      count ++;
      /* Show 10 transactions per line */
      if ((count % 10) == 0)
	msg__ ("\n");
      msg__ ("%s  ", cfdp_trans_as_string (t));
    }

  msg__ ("\n\n");
}



/*=r=*************************************************************************/
static boolean m__robustness_test (void)
     /* WHAT IT DOES:  Runs an automated test of the robustness of the
      *   CFDP engine.  The engine should reject inputs that are either
      *   invalid, or that violate compile-time constraints on array sizes.
      */
{
  u_int_4       bytes;
  u_int_4       file_size;
  ID            id;
  DATA          pdu;
  u_int_4       seconds;
  char          string [1024];
  boolean       success;
  TRANSACTION   trans;
  TIMER_TYPE    type;
  char          value [1024];
  /*------------------------------------------------------------*/

  msg__ ("\nCFDP Robustness Test\n");
  
  success = YES;
  
  /*--------------------------------------*/
  /* Pass null-pointers wherever possible */
  /*--------------------------------------*/
  
  printf ("\n>>>  Passing null-pointers wherever possible...\n");

  printf ("\n>>>  ...to cfdp_give_request:\n");
  if (cfdp_give_request (NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_request accepted a null-pointer.\n");
    }
  
  printf ("\n>>>  ...to cfdp_set_mib_parameter (3 times):\n");
  if (cfdp_set_mib_parameter ("Boogie_On", NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_set_mib_parameter accepted "
	      "a null-pointer (1).\n");
    }
  
  if (cfdp_set_mib_parameter (NULL, "Boogie_on"))
    {
      success = NO;
      printf ("<FAILED> cfdp_set_mib_parameter accepted "
	      "a null-pointer (2).\n");
    }
  
  if (cfdp_set_mib_parameter (NULL, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_set_mib_parameter accepted "
	      "a null-pointer (3).\n");
    }
  
  printf ("\n>>>  ...to cfdp_get_mib_parameter (3 times):\n");
  if (cfdp_get_mib_parameter ("Boogie_On", NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_get_mib_parameter accepted "
	      "a null-pointer (1).\n");
    }
  
  if (cfdp_get_mib_parameter (NULL, value))
    {
      success = NO;
      printf ("<FAILED> cfdp_get_mib_parameter accepted "
	      "a null-pointer (2).\n");
    }
  
  if (cfdp_get_mib_parameter (NULL, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_get_mib_parameter accepted "
	      "a null-pointer (3).\n");
    }
  
  printf ("\n>>>  testing cfdp_transaction_status:\n");
  if (cfdp_transaction_status (trans, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_transaction_status accepted a null-pointer\n");
    }
  
  printf ("\n>>>  ...to cfdp_transaction_timer_status (2 times):\n");
  if (cfdp_transaction_timer_status (trans, NULL, &seconds))
    {
      success = NO;
      printf ("<FAILED> cfdp_transaction_timer_status accepted "
	      "a null-pointer (1)\n");
    }
  
  if (cfdp_transaction_timer_status (trans, &type, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_transaction_timer_status accepted "
	      "a null-pointer (2)\n");
    }
  
  printf ("\n>>>  ...to cfdp_transaction_progress (2 times):\n");
  if (cfdp_transaction_progress (trans, NULL, &file_size))
    {
      success = NO;
      printf ("<FAILED> cfdp_transaction_progress accepted "
	      "a null-pointer (1)\n");
    }
  
  if (cfdp_transaction_progress (trans, &bytes, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_transaction_progress accepted "
	      "a null-pointer (2)\n");
    }
  
  printf ("\n>>>  ...to cfdp_id_from_string (2 times):\n");
  if (cfdp_id_from_string (NULL, &id))
    {
      success = NO;
      printf ("<FAILED> cfdp_id_from_string accepted "
	      "a null-pointer (1)\n");
    }
  
  if (cfdp_id_from_string (string, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_id_from_string accepted "
	      "a null-pointer (2)\n");
    }
  
  printf ("\n>>>  ...to cfdp_trans_from_string (2 times):\n");
  strcpy (string, "23_1");
  if (cfdp_trans_from_string (string, NULL))
    {
      success = NO;
      printf ("<FAILED> cfdp_trans_from_string accepted "
	      "a null-pointer (1)\n");
    }
  
  if (cfdp_trans_from_string (NULL, &trans))
    {
      success = NO;
      printf ("<FAILED> cfdp_trans_from_string accepted "
	      "a null-pointer (1)\n");
    }
  

  /*-------------------------------------------*/
  /* Pass various "invalid" pdus to the engine */
  /*-------------------------------------------*/

  printf ("\n>>> Passing various unacceptable pdus to the engine...\n");

  printf ("\n>>> ...PDU too short (2 times):\n");

  pdu.length = 0;
  memset (pdu.content, 0x00, sizeof(pdu.content));
  if (cfdp_give_pdu (pdu))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_pdu accepted a zero-length PDU.\n");
    }
  
  pdu.length = 3;
  memset (pdu.content, 0x00, sizeof(pdu.content));
  if (cfdp_give_pdu (pdu))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_pdu accepted a 3-byte PDU.\n");
    }

  /* Note;  This routine does not contain a test for a pdu that is too long
   * because:
   *   1) the engine accepts (and truncates if necessary) Filedata pdus
   *   2) ditto for Nak pdus
   *   3) all other pdus except Metadata have fixed format
   *   (I haven't figured out how to handle Metadata pdus that exceed
   *   our storage capacity)
   */

  printf ("\n>>> ...PDU with invalid directive-code:\n");
  pdu.length = 55;
  memset (pdu.content, 0x00, sizeof(pdu.content));
  pdu.content[2] = 0xFF;  /* Reasonable data-length */
  if (cfdp_give_pdu (pdu))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_pdu accepted invalid dir-code.\n");
    }

  printf ("\n>>> ...PDU entity-id too long:\n");
  /* Strictly speaking, this pdu is valid, but the entity-id length
   * exceeds a compile-time restriction of the engine, so the engine 
   * should not try to store it.   (see MAX_ID_LENGTH)
   */
  
  pdu.length = 20;
  memset (pdu.content, 0x00, sizeof(pdu.content));
  pdu.content[0] = 0x10;  /* Filedata pdu */
  pdu.content[2] = 0xFF;  /* Reasonable data-length */
  pdu.content[3] = 0x70;  /* 8-byte entity-ids, 1-byte trans */
  pdu.content[7] = 0x07;  /* Metadata pdu */
  if (cfdp_give_pdu (pdu))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_pdu accepted entity-id too long.\n");
    }

  printf ("\n>>> ...PDU trans-seq-num too long:\n");
  /* Strictly speaking, this pdu is valid, but the trans-seq-num length
   * exceeds a built-in restriction of the engine, so the engine should
   * not try to store it.     (trans-seq-num hard-coded to 4 bytes)
   */

  pdu.length = 20;
  memset (pdu.content, 0x00, sizeof(pdu.content));
  pdu.content[0] = 0x10;  /* Filedata pdu */
  pdu.content[2] = 0xFF;  /* Reasonable data-length */
  pdu.content[3] = 0x07;  /* 1-byte entity-ids, 8-byte trans */
  if (cfdp_give_pdu (pdu))
    {
      success = NO;
      printf ("<FAILED> cfdp_give_pdu accepted trans-seq-num too long.\n");
    }

  /*---------------------------------------------------*/
  /* Try various invalid calls to set an MIB parameter */
  /*---------------------------------------------------*/

  if (cfdp_set_mib_parameter ("boogie_on_", "25"))
    {
      success = NO;
      printf ("<FAILED> cfdp_set_mib_parameter accepted bogus parameter.\n");
    }

  /* Make sure the syntax is correct */
  if (!cfdp_set_mib_parameter ("ack_limit", "5"))
    {
      success = NO;
      printf ("<FAILED> 'valid' call to set ack-limit failed.\n");
    }

  if (cfdp_set_mib_parameter ("ack_limit", "-5"))
    {
      success = NO;
      printf ("<FAILED> ack-limit set to negative number.\n");
    }

  /* Make sure the syntax is correct */
  if (!cfdp_set_mib_parameter ("outgoing_file_chunk_size", "500"))
    {
      success = NO;
      printf ("<FAILED> 'valid' call to set file-chunk-size failed.\n");
    }

  if (cfdp_set_mib_parameter ("outgoing_file_chunk_size", "-5"))
    {
      success = NO;
      printf ("<FAILED> outgoing-file-chunk-size set to negative number.\n");
    }

  sprintf (string, "%u", MAX_FILE_CHUNK_SIZE+1);
  if (cfdp_set_mib_parameter ("outgoing_file_chunk_size", string))
    {
      success = NO;
      printf ("<FAILED> outgoing-file-chunk-size set to giant number.\n");
    }

  if (cfdp_set_mib_parameter ("my_id", "GoBabyGo"))
    {
      success = NO;
      printf ("<FAILED> my-id set to bogus value.\n");
    }

  return (success);
}



/*=r=************************************************************************/
static void m__execute_user_input (const char *user_input)
     /* WHAT IT DOES:  Parses and executes input commands from the user. */
{
  char             arg1 [32];
  char             arg2 [32];
  char             arg3 [32];
  char             arg4 [32];
  static boolean   echo = NO;
  int              i;
  char             string [1024];
  SUMMARY_STATUS   summary;
  u_int_4          total_trans;
  /*------------------------------------------------------------*/

  if (echo)
    msg__ ("> %s", user_input);

  /* Extract all args (tokens) from the given input, and convert
   * some of them to lowercase.
   */
  strcpy (arg1, "\0");
  strcpy (arg2, "\0");
  strcpy (arg3, "\0");
  strcpy (arg4, "\0");
  sscanf (user_input, "%32s %32s %32s %32s", arg1, arg2, arg3, arg4);
  for (i=0; i<strlen(arg1); i++)
    arg1[i] = tolower(arg1[i]);
  for (i=0; i<strlen(arg2); i++)
    arg2[i] = tolower(arg2[i]);
  

  /* Provide a way for the interactive User to exit this program */
  if (!strncmp (arg1, "exit", 2))
    {
      msg__ ("Bye.\n");
      exit (0);
    }

  else if (!strcmp (arg1, "update"))
    {
      m_cycles_between_updates = atoi (arg2);
      msg__ ("Cycles between updates set to %u.\n", 
	     m_cycles_between_updates);
    }

  else if (!strcmp (arg1, "class+"))
    {
      if (!strcmp (arg2, "all"))
        cfdp_enable_message_class (0);
      else if (!strcmp (arg2, "indications"))
        cfdp_enable_message_class (CFDP_MSG_INDICATIONS);
      else if (!strcmp (arg2, "debug_memory_use"))
        cfdp_enable_message_class (CFDP_MSG_DEBUG_MEMORY_USE);
      else if (!strcmp (arg2, "debug_nak"))
        cfdp_enable_message_class (CFDP_MSG_DEBUG_NAK);
      else if (!strcmp (arg2, "debug_pdu"))
        cfdp_enable_message_class (CFDP_MSG_DEBUG_PDU);
      else if (!strcmp (arg2, "pdu_filedata"))
        cfdp_enable_message_class (CFDP_MSG_PDU_FILEDATA);
      else if (!strcmp (arg2, "pdu_non_filedata"))
        cfdp_enable_message_class (CFDP_MSG_PDU_NON_FILEDATA);
      else if (!strcmp (arg2, "pdu_retransmitted_fd"))
        cfdp_enable_message_class (CFDP_MSG_PDU_RETRANSMITTED_FD);
      else if (!strcmp (arg2, "state_all"))
        cfdp_enable_message_class (CFDP_MSG_STATE_ALL);
      else if (!strcmp (arg2, "state_change"))
        cfdp_enable_message_class (CFDP_MSG_STATE_CHANGE);
      else
        printf ("<INPUT_ERROR> Unrecognized message class (%s).\n", arg2);
    }

  else if (!strcmp (arg1, "class-"))
    {
      if (!strcmp (arg2, "all"))
        cfdp_disable_message_class (0);
      else if (!strcmp (arg2, "indications"))
        cfdp_disable_message_class (CFDP_MSG_INDICATIONS);
      else if (!strcmp (arg2, "debug_memory_use"))
        cfdp_disable_message_class (CFDP_MSG_DEBUG_MEMORY_USE);
      else if (!strcmp (arg2, "debug_nak"))
        cfdp_disable_message_class (CFDP_MSG_DEBUG_NAK);
      else if (!strcmp (arg2, "debug_pdu"))
        cfdp_disable_message_class (CFDP_MSG_DEBUG_PDU);
      else if (!strcmp (arg2, "pdu_filedata"))
        cfdp_disable_message_class (CFDP_MSG_PDU_FILEDATA);
      else if (!strcmp (arg2, "pdu_non_filedata"))
        cfdp_disable_message_class (CFDP_MSG_PDU_NON_FILEDATA);
      else if (!strcmp (arg2, "pdu_retransmitted_fd"))
        cfdp_disable_message_class (CFDP_MSG_PDU_RETRANSMITTED_FD);
      else if (!strcmp (arg2, "state_all"))
        cfdp_disable_message_class (CFDP_MSG_STATE_ALL);
      else if (!strcmp (arg2, "state_change"))
        cfdp_disable_message_class (CFDP_MSG_STATE_CHANGE);
      else
        printf ("<INPUT_ERROR> Unrecognized message class (%s).\n", arg2);
    }

  else if (!strncmp (arg1, "disable_engine_messages", 2))
    {
      msg__ ("Disabling engine messages (registering 'no-op' printf).\n");
      register_printf (printf_noop);
    }

  else if (!strcmp (arg1, "echo"))
    echo = YES;

  else if (!strncmp (arg1, "enable_engine_messages", 2))
    {
      msg__ ("Enabling engine messages (registering normal printf).\n");
      register_printf (printf);
    }

  else if (!strncmp (arg1, "freeze", 1))
    {
      msg__ ("Will 'freeze' the engine.\n");
      cfdp_give_request ("freeze");
    }

  else if (!strncmp (arg1, "get", 3))
    {
      cfdp_get_mib_parameter (arg2, string);
      msg__ ("Get_mib: %s = %s.\n", arg2, string);
    }

  else if ((!strncmp (arg1, "help", 1)) || (!strcmp (arg1, "?")))
    m__give_detailed_help ();

  else if (!strncmp (arg1, "list", 1))
    /* Show list of transactions */
    m__show_list_of_transactions ();

  else if (!strcmp (arg1, "mib"))
    msg__ ("%s\n", cfdp_mib_as_string());

  else if (!strcmp (arg1, "reset_totals"))
    {
      cfdp_reset_totals ();
      summary = cfdp_summary_status ();
      total_trans = summary.how_many_receivers + summary.how_many_senders;
      msg__ ("\nSummary:\n"
             "   %lu trans (%lu senders, %lu receivers), "
             "%lu frozen, %lu suspended.\n"
             "   Totals:  %lu sent, %lu received, "
             "%lu send-fail, %lu recv-fail\n",
             total_trans, summary.how_many_senders, summary.how_many_receivers,
             summary.how_many_frozen, summary.how_many_suspended,
	     summary.total_files_sent, summary.total_files_received,
	     summary.total_unsuccessful_senders,
	     summary.total_unsuccessful_receivers);
    }
      
  else if (!strcmp (arg1, "robust?"))
    {
      if (m__robustness_test ())
	msg__ ("Engine robustness test passed.\n\n\n");
      else
	{
	  msg__ ("Exiting due to failure of engine robustness test.\n");
	  exit (1);
	}
    }

  else if (!strncmp (arg1, "set", 3))
    {
      msg__ ("Setting MIB parameter '%s' to '%s'.\n", arg2, arg3);
      cfdp_set_mib_parameter (arg2, arg3);
    }

  else if (!strcmp (arg1, "sim"))
    link_sim__directive (arg2);
  
  else if (!strncmp (arg1, "summary", 3))
    {
      summary = cfdp_summary_status ();
      total_trans = summary.how_many_receivers + summary.how_many_senders;
      msg__ ("\nSummary:\n"
             "   %lu trans (%lu senders, %lu receivers), "
             "%lu frozen, %lu suspended.\n"
             "   Totals:  %lu sent, %lu received, "
             "%lu send-fail, %lu recv-fail\n",
             total_trans, summary.how_many_senders, summary.how_many_receivers,
             summary.how_many_frozen, summary.how_many_suspended,
	     summary.total_files_sent, summary.total_files_received,
	     summary.total_unsuccessful_senders,
	     summary.total_unsuccessful_receivers);
    }

  else if (!strncmp (arg1, "thaw", 1))
    {
      msg__ ("Will 'thaw' the engine.\n");
      cfdp_give_request ("thaw");
    }

  else if (!strcmp (arg1, "v"))
    /* Show trans status once */
    m__show_transactions_status ();

  else if (!strcmp (arg1, "detailed_status"))
    /* Show detailed trans status */
    m__show_trans_details (arg2);

  else if (!strcmp (arg1, "n"))
    /* Toggle periodic trans status display */
    {
      if (m_periodic_status)
	{
	  m_periodic_status = NO;
	  msg__ ("Periodic status disabled.\n");
	}
      else
	{
	  m_periodic_status = YES;
	  msg__ ("Periodic status enabled.\n");
	}
    }	

  else if (!strcmp (arg1, "p1"))
    {
      strcpy (string, "put cfdp_flight 24 88");
      cfdp_give_request (string);
    }

  else if (!strcmp (arg1, "p2"))
    {
      strcpy (string, "put cfdp_ground 24 89");
      cfdp_give_request (string);
    }

  else if (isdigit (arg1[0]))
    /* Set the Link Simulator's success rate */
    {
      msg__ ("Setting the Link Simulator success rate to %s%%.\n", arg1);
      sprintf (string, "success_rate=%s", arg1);
      link_sim__directive (string);
    }

  else if (strlen(arg1) > 0)
    {
      if (!cfdp_give_request (user_input))
        msg__ ("<Invalid_User_Input> (%s)\n", arg1);
    }        
}



/*=r=************************************************************************/
void cfdp (int argc, char *argv[])
   {
     boolean     any_input;
     u_int_4     cycle;
     ID          my_entity_id;
     char        my_entity_id_as_string [128];
     DATA        pdu;
     char        user_input [1024];
   /*------------------------------------------------------------*/
     msg__ ("CFDP Sample Application Version %s ", PROGRAM_VERSION);

     if ((argc == 2) && (!strcmp (argv[1], "-?")))
       m__give_help_and_exit ();
     else if ((argc == 2) && (toupper(argv[1][0]) == 'H'))
       m__give_help_and_exit ();

     /* Register callback routines */
     register_indication (indication);
     register_pdu_output_open (pdu_output__open);
     register_pdu_output_ready (pdu_output__ready);
     register_pdu_output_send (pdu_output__send);
     
     m__show_config ();

     /* Determine my entity-id */
     strcpy (my_entity_id_as_string, DEFAULT_CFDP_NODE_AS_STRING);
     if (argc >= 2)
       strcpy (my_entity_id_as_string, argv[1]);

     /* Determine location of hosts-table */
     if (argc >= 3)
       comm__set_hosts_table (argv[2]);

     /* Initialize the MIB */
     cfdp_set_mib_parameter (MIB_MY_ID, my_entity_id_as_string);
     
     msg__ ("\n%s\n", cfdp_mib_as_string());

     if (!cfdp_id_from_string (my_entity_id_as_string, &my_entity_id))
       {
         msg__ ("<ERROR> My ID (%s) is invalid.\n", my_entity_id_as_string);
         exit (1);
       }
       
     if (!pdu_input__init (my_entity_id))
       {
         msg__ ("<FATAL>  Unable to initialize my comm port.\n");
         exit (1);
       }

     link_type__set (LINK_TWO_WAY);


     cycle = 0;
     for (;;)
       {
         any_input = NO;
         if (user_input__poll (user_input))
           {
             m__execute_user_input (user_input);
           }
         if (pdu_input__poll (&pdu))
           {
             any_input = YES;
             cfdp_give_pdu (pdu);
           }
         if (!any_input)
           {
             /* Cycle each transaction.  This includes deleting any 
              * transactions that have completed, and giving each trans the
              * chance to make progress (check for expired timers, etc).
              */
             cfdp_cycle_each_transaction ();
             usleep__microseconds (1);
             fflush (stdout);
           }

	 /* If directed to do so, display status periodically */
	 if (m_periodic_status)
	   {
	     cycle ++;
	     if (cycle >= m_cycles_between_updates)
	       {
		 m__show_transactions_status ();
		 cycle = 0;
	       }
	   }
       }
   }



/*=r=*************************************************************************/
void m__sigpipe_handler (int signal)
     /* WHAT IT DOES:  ALlows us to be aware of a lost pipe.  (Exits). */
{
  char           msg [128];
  /*------------------------------------------------------------*/
  
  system ("date");
  strcpy (msg, "<FATAL> SIGPIPE signal received.\n");
  printf ("%s", msg);
  fflush (stdout);
  exit (1);
}



/*=r=************************************************************************/
int main (int argc, char *argv[])
   {
     struct sigaction      new_action;
     struct sigaction      old_action;
   /*------------------------------------------------------------*/

     /* Catch the SIGPIPE signal */
     sigemptyset (&new_action.sa_mask);
     new_action.sa_flags = 0;
     new_action.sa_handler = m__sigpipe_handler;
     if (sigaction (SIGPIPE, &new_action, &old_action) != 0)
       {
	 printf ("<FATAL> Unable to register SIGPIPE signal-handler.\n");
	 exit (1);
       }

     cfdp (argc, argv);
     return (0);
   }

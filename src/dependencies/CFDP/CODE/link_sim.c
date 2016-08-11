/* FILE: link_sim.c    Comm Link Simulator module. 
 * VERSION: 2.3k 2004_09_20
 * SPECS:  link_sim.h
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 * SKETCH OF HOW IT WORKS:
 *   Normal mode:
 *     Each input Pdu is stored in Slot #1 and immediately retreived.
 *   Duplicate mode:
 *     Each input Pdu is stored in Slot #1 and Slot #2 and then both slots
 *     are immediately retreived.
 *   Reorder mode:
 *     First input Pdu is stored in Slot #2, and is not immediately retreived.
 *     Second input Pdu is stored in Slot #1, and then both are retreived.
 *   "Drop one" modes:
 *     First input Pdu of the specified type is discarded, and the mode 
 *     immediately returns to Normal.
 *   "Drop all" modes:
 *     All Pdus of the specified type(s) are dropped until a directive arrives
 *     which changes the mode.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfdp_code.h"

#define  UPPER_NIBBLE(b) ((b & 0xF0) >> 4)




typedef enum 
{ 
  _DONT_KNOW_, _MD_, _FD_, _EOF_, _ACK_EOF_, _NAK_, _FIN_, _ACK_FIN_ 
} _PDU_TYPE_;

static CORRUPT              m_corrupt = CORRUPT_NONE;
static u_int_4              m_delay_between_pdus = 0;
static boolean              m_is_slot_one_occupied = NO;
static boolean              m_is_slot_two_occupied = NO;
static SIM_MODE             m_mode = SIM_MODE_NORMAL;
static boolean              m_output_messages_for_dirs = YES;
static boolean              m_output_messages_general = NO;
static DATA                 m_slot_one;
static DATA                 m_slot_two;
static u_int_2              m_success_rate = 100;




/*=r=************************************************************************/
static DATA m__copy_pdu (DATA pdu)
   {
     static DATA         copy;
   /*------------------------------------------------------------*/

     if (pdu.length > MAX_DATA_LENGTH)
       /* PROBLEM! */
       {
	 copy.length = MAX_DATA_LENGTH;
     msg__ ("^^^ m__copy_pdu:  Data is too long! (%lu > %lu).\n",
		 pdu.length, (u_int_4) MAX_DATA_LENGTH);
     msg__ ("(will truncate the pdu)\n");
	 memcpy (&copy.content, &pdu.content, MAX_DATA_LENGTH);
       }
     else
       {
	 copy.length = pdu.length;
	 memcpy (&copy.content, &pdu.content, pdu.length);
       }
       
     return (copy);
   }



/*=r=*************************************************************************/
static void m__corrupt_pdu (DATA *pdu)
     /* WHAT IT DOES:  Corrupts the appropriate field in the given PDU. */
{
  int             entity_id_length;
  int             header_length;
  int             trans_seq_num_length;
  /*------------------------------------------------------------*/

  entity_id_length = ((pdu->content[3] & 0x70) >> 4) + 1;
  trans_seq_num_length = (pdu->content[3] & 0x07) + 1;
  header_length = 4 + entity_id_length + trans_seq_num_length + 
    entity_id_length;
  if (pdu->length <= header_length)
    {
      msg__ ("Link_sim:  Will not corrupt an invalid pdu.\n");
      return;
    }

  if (pdu->content[header_length] == 0x04)
    /* This is an EOF PDU. */
    {
      msg__ ("^^^ EOF pdu.  !!!!!! \n");
      if (pdu->length < header_length + 9)
	{
	  msg__ ("Link_sim:  Will not corrupt an invalid EOF pdu.\n");
	  return;
	}
      if ((pdu->content[header_length+1] & 0xF0) == 0x00)
	/* This is an EOF-no-error PDU */
	{
	  msg__ ("^^^ EOF-no-error pdu. !!!!!! \n");
	  if (m_corrupt == CORRUPT_EOF_CHECKSUM)
	    {
	      msg__ ("^^^ will corrupt the checksum... !!!!!!!\n");
	      /* Corrupt the checksum field */
	      if (pdu->content[header_length+2] == 0xFF)
		{
		  msg__ ("Link_sim:  Corrupting checksum in EOF-no-error: "
			 "%2x -> 00.\n", pdu->content[header_length+2]);
		  pdu->content[header_length+2] = 0x00;
		}
	      else
		{
		  msg__ ("Link_sim:  Corrupting checksum in EOF-no-error: "
			 "%2x -> FF.\n", pdu->content[header_length+2]);
		  pdu->content[header_length+2] = 0xFF;
		}
		  
	    }
	  
	  else if (m_corrupt == CORRUPT_EOF_FILE_SIZE)
	    {
	      /* Corrupt the file-size field (make it smaller) */
	      if (pdu->content[header_length+9] != 0x00)
		/* This should usually be the case */
		{
		  msg__ ("Link_sim:  Corrupting file-size in EOF: "
			 "0x%2x%2x%2x%2x -> 0x%2x%2x%2x00.\n",
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9],
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8]);
		  pdu->content[header_length+9] = 0x00;
		}
		  
	      else if (pdu->content[header_length+8] != 0x00)
		{
		  msg__ ("Link_sim:  Corrupting file-size in EOF: "
			 "0x%2x%2x%2x%2x -> 0x%2x%2x00%2x.\n",
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9],
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+9]);
		  pdu->content[header_length+8] = 0x00;
		}

	      else if (pdu->content[header_length+7] != 0x00)
		{
		  msg__ ("Link_sim:  Corrupting file-size in EOF: "
			 "0x%2x%2x%2x%2x -> 0x%2x00%2x%2x.\n",
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9],
			 pdu->content[header_length+6],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9]);
		  pdu->content[header_length+7] = 0x00;
		}

	      else if (pdu->content[header_length+6] != 0x00)
		{
		  msg__ ("Link_sim:  Corrupting file-size in EOF: "
			 "0x%2x%2x%2x%2x -> 0x00%2x%2x%2x.\n",
			 pdu->content[header_length+6],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9],
			 pdu->content[header_length+7],
			 pdu->content[header_length+8],
			 pdu->content[header_length+9]);
		  pdu->content[header_length+6] = 0x00;
		}

	      else
		msg__ ("Link-sim:  Will not corrupt file-size of 0.\n");
	    }
	  else
	    msg__ ("Link_sim:  Heads-up: no corruption enabled.\n");
	}
    }
}



/*=r=************************************************************************/
_PDU_TYPE_ m__pdu_type (DATA pdu)
     /* WHAT IT DOES:  Examines the given PDU, and returns its type. */
{
  u_int_1           dir_code;
  int               length_of_header;
  int               length_of_id;
  int               length_of_trans_num;
  _PDU_TYPE_        type;
  /*------------------------------------------------------------*/
  type = _DONT_KNOW_;
  ASSERT__ (pdu.length > 8);
  
  if (pdu.content[0] & 0x10)
    /* It's Filedata */
    return (_FD_);
  
  /* It's a File Directive, but which one? */
  length_of_id = ((pdu.content[3] & 0x70) >> 4) + 1;
  length_of_trans_num = (pdu.content[3] & 0x07) + 1;
  length_of_header = 4 + length_of_id + length_of_trans_num + length_of_id;
  if (pdu.length <= length_of_header + 1)
    {
      msg__ ("<WARNING> (%s/%u) Invalid PDU; length %u, hdr-len %u.\n",
             __FILE__, __LINE__, pdu.length, length_of_header);
      ASSERT__BUG_DETECTED;
      return (type);
    }

  dir_code = pdu.content[length_of_header];
  
  if (dir_code == 4)
    type = _EOF_;
  
  else if (dir_code == 5)
    type = _FIN_;
  
  else if (dir_code == 6)
    /* It's an Ack, but which one? */
    {
      if (UPPER_NIBBLE (pdu.content[length_of_header+1]) == 4)
        type = _ACK_EOF_;
      else if (UPPER_NIBBLE (pdu.content[length_of_header+1]) == 5)
        type = _ACK_FIN_;
      else
        /* This Ack should have been for either an EOF or Fin PDU */
        msg__ ("<WARNING> at line %u of %s.\n", __LINE__, __FILE__);
    }
  
  else if (dir_code == 7)
    type = _MD_;
  
  else if (dir_code == 8)
    type = _NAK_;
  
  else
    /* PDU is not recognized */
    msg__ ("<WARNING> at line %u of %s.\n", __LINE__, __FILE__);

return (type);
}



/*=r=************************************************************************/
static u_int_1 m__random_percentage (void)
     /* WHAT IT DOES:  Returns a random number between 0 and 100 inclusive. */
   {
   /*------------------------------------------------------------*/
     return (rand() % 101);
   }



/*=r=************************************************************************/
static void m__store_pdu_in_slot_one (DATA pdu)
   {
   /*------------------------------------------------------------*/
     m_slot_one = pdu;
     m_is_slot_one_occupied = YES;
   }



/*=r=************************************************************************/
static void m__store_pdu_in_slot_two (DATA pdu)
   {
   /*------------------------------------------------------------*/
     m_slot_two = pdu;
     m_is_slot_two_occupied = YES;
   }



/*=r=************************************************************************/
static void m__upcase (char *string)
   {
     int        i;
   /*------------------------------------------------------------*/
     for (i=0; i<strlen(string); i++)
       string[i] = toupper (string[i]);
   }



/*=r=************************************************************************/
void link_sim__directive (char *dir)
   {
   /*------------------------------------------------------------*/
     m__upcase (dir);

     if (!strcmp (dir, "NORMAL"))
       {
	 m_mode = SIM_MODE_NORMAL;
         msg__ ("Link_Sim:  Set to Normal Mode.\n");
       }

     else if (!strcmp (dir, "DUPLICATE"))
       {
	 m_mode = SIM_MODE_DUPLICATE;
         msg__ ("Link_Sim:  Set to Duplicate Mode.\n");
       }

     else if (!strcmp (dir, "REORDER"))
       {
	 m_mode = SIM_MODE_REORDER;
         msg__ ("Link_Sim:  Set to Reorder Mode.\n");
       }

     else if (!strcmp (dir, "DROP_ONE_MD"))
       {
	 m_mode = SIM_MODE_DROP_ONE_MD;
         msg__ ("Link_Sim:  Will drop one MD.\n");
       }

     else if (!strcmp (dir, "DROP_ONE_EOF"))
       {
	 m_mode = SIM_MODE_DROP_ONE_EOF;
         msg__ ("Link_Sim:  Will drop one EOF.\n");
       }

     else if (!strcmp (dir, "DROP_ONE_FIN"))
       {
	 m_mode = SIM_MODE_DROP_ONE_FIN;
         msg__ ("Link_Sim:  Will drop one Fin.\n");
       }

     else if (!strcmp (dir, "DROP_ONE_ACK_EOF"))
       {
	 m_mode = SIM_MODE_DROP_ONE_ACK_EOF;
         msg__ ("Link_Sim:  Will drop one Ack-EOF.\n");
       }

     else if (!strcmp (dir, "DROP_ONE_ACK_FIN"))
       {
	 m_mode = SIM_MODE_DROP_ONE_ACK_FIN;
         msg__ ("Link_Sim:  Will drop one Ack-Fin.\n");
       }

     else if (!strcmp (dir, "DROP_ALL_BUT_EOF"))
       {
	 m_mode = SIM_MODE_DROP_ALL_BUT_EOF;
         msg__ ("Link_Sim:  Will drop all but EOF.\n");
       }

     else if (!strcmp (dir, "DROP_ALL_BUT_MD"))
       {
	 m_mode = SIM_MODE_DROP_ALL_BUT_MD;
         msg__ ("Link_Sim:  Will drop all but Metadata.\n");
       }

     else if (!strcmp (dir, "DROP_ALL_ACK_AND_FIN"))
       {
	 m_mode = SIM_MODE_DROP_ALL_ACK_AND_FIN;
         msg__ ("Link_Sim:  Will drop all Acks and Fins.\n");
       }

     else if (!strcmp (dir, "DROP_ALL_NAK"))
       {
	 m_mode = SIM_MODE_DROP_ALL_NAK;
         msg__ ("Link_Sim:  Will drop all Naks.\n");
       }

     else if (!strcmp (dir, "DROP_ALL_FIN"))
       {
	 m_mode = SIM_MODE_DROP_ALL_FIN;
         msg__ ("Link_Sim:  Will drop all Fins.\n");
       }

     else if (!strcmp (dir, "DROP_ALL"))
       {
	 m_mode = SIM_MODE_DROP_ALL;
         msg__ ("Link_Sim:  Will drop all PDUs.\n");
       }

     else if (!strncmp (dir, "DELAY_BETWEEN_PDUS=", 19))
       {
         sscanf (dir+19, "%lu", &m_delay_between_pdus);
         msg__ ("Link_Sim:  Delay between pdus set to %lu microseconds.\n",
                m_delay_between_pdus);
       }

     else if (!strncmp (dir, "SUCCESS_RATE=", 13))
       {
         sscanf (dir+13, "%u", &m_success_rate);
         msg__ ("Link_Sim:  Success rate set to %u%%.\n", m_success_rate);
       }

     else if (!strcmp (dir, "CORRUPT_NONE"))
       {
	 m_corrupt = CORRUPT_NONE;
	 msg__ ("Link_Sim:  Will not corrupt any PDUs.\n");
       }

     else if (!strcmp (dir, "CORRUPT_EOF_CHECKSUM"))
       {
	 m_corrupt = CORRUPT_EOF_CHECKSUM;
	 msg__ ("Link_Sim:  Will corrupt checksum in outgoing "
		"EOF-no-error PDUs.\n");
       }

     else if (!strcmp (dir, "CORRUPT_EOF_FILE_SIZE"))
       {
	 m_corrupt = CORRUPT_EOF_FILE_SIZE;
	 msg__ ("Link_Sim:  Will corrupt file-size in outgoing "
		"EOF-no-error PDUs.\n");
       }

     else
       msg__ ("<WARNING> Unrecognized link_sim directive (%s).\n", dir);
   }




/*=r=************************************************************************/
void link_sim__give_pdu (DATA pdu)
   {
     DATA           pdu_copy;
     _PDU_TYPE_     pdu_type;
   /*------------------------------------------------------------*/

     /* Copy the pdu */
     pdu_copy = m__copy_pdu (pdu);

     if (m_mode == SIM_MODE_NORMAL)
       /* Store one copy of the Pdu "success_rate" percentage of the time */
       {
         if (m__random_percentage() <= m_success_rate)
           {
           m__store_pdu_in_slot_one (pdu_copy);
           }
         else
           /* Discard the pdu */
           {
             if (m_output_messages_general)
               {
                 pdu_type = m__pdu_type (pdu_copy);
                 if (pdu_type == _FD_)
                   msg__ ("!Link_Sim     Random droppage (Filedata)\n");
                 else
                   msg__ ("!Link_Sim     Random droppage (control PDU)\n");
               }
           }
       }

     else if (m_mode == SIM_MODE_DUPLICATE)
       {
         if (m__random_percentage() <= LINK_SIM_DUPLICATE_PERCENTAGE)
           /* Store one copy */
           m__store_pdu_in_slot_one (pdu_copy);
         else
           /* Store two copies */
           {
             if (m_output_messages_general)
               msg__ ("!Link_Sim     Random duplication.\n");
             m__store_pdu_in_slot_one (pdu_copy);
             m__store_pdu_in_slot_two (pdu_copy);
           }
       }

     else if (m_mode == SIM_MODE_REORDER)
       {
         if ((m__random_percentage() <= LINK_SIM_REORDER_PERCENTAGE) ||
             (m_is_slot_two_occupied))
           /* Do the usual (i.e. store one copy) */
           m__store_pdu_in_slot_one (pdu_copy);
         else
           /* Cause reordering by putting this Pdu into slot #2 
            * instead of slot #1.
            */
           {
             if (m_output_messages_general)
               msg__ ("!Link_Sim     Random reordering.\n");
             m__store_pdu_in_slot_two (pdu_copy);
           }
       }

     else if (m_mode == SIM_MODE_DROP_ONE_MD)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _MD_)
           /* Drop this one MD, then continue normally */
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropped one MD)\n");
             m_mode = SIM_MODE_NORMAL;
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ONE_EOF)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _EOF_)
           /* Drop this one EOF, then continue normally */
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropped one EOF)\n");
             m_mode = SIM_MODE_NORMAL;
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ONE_FIN)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _FIN_)
           /* Drop this one FIN, then continue normally */
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropped one FIN)\n");
             m_mode = SIM_MODE_NORMAL;
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ONE_ACK_EOF)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _ACK_EOF_)
           /* Drop this one ACK_EOF, then continue normally */
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropped one ACK_EOF)\n");
             m_mode = SIM_MODE_NORMAL;
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ONE_ACK_FIN)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _ACK_FIN_)
           /* Drop this one ACK_FIN, then continue normally */
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropped one ACK_FIN)\n");
             m_mode = SIM_MODE_NORMAL;
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ALL_BUT_MD)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _MD_)
           m__store_pdu_in_slot_one (pdu_copy);
         else
           {
	     if (((pdu_type == _FD_) && (m_output_messages_general)) ||
		 m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropping all but MD)\n");
           }
       }

     else if (m_mode == SIM_MODE_DROP_ALL_BUT_EOF)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _EOF_)
           m__store_pdu_in_slot_one (pdu_copy);
         else
           {
	     if (((pdu_type == _FD_) && (m_output_messages_general)) ||
		 m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropping all but EOF)\n");
           }
       }

     else if (m_mode == SIM_MODE_DROP_ALL_ACK_AND_FIN)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if ((pdu_type == _ACK_EOF_) ||
             (pdu_type == _ACK_FIN_) ||
             (pdu_type == _FIN_))
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropping all ACK & FIN)\n");
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ALL_NAK)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _NAK_)
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropping all NAK)\n");
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ALL_FIN)
       {
         pdu_type = m__pdu_type (pdu_copy);
         if (pdu_type == _FIN_)
           {
             if (m_output_messages_for_dirs)
               msg__ ("!Link_Sim     (dropping all FIN)\n");
           }
         else
           m__store_pdu_in_slot_one (pdu_copy);
       }

     else if (m_mode == SIM_MODE_DROP_ALL)
       { 
	 pdu_type = m__pdu_type (pdu_copy);
	 if ((pdu_type == _FD_) && m_output_messages_general)
           msg__ ("!Link_Sim     (dropping all Pdus) (FD)\n");
	 else if ((pdu_type != _FD_) && m_output_messages_for_dirs)
           msg__ ("!Link_Sim     (dropping all Pdus) (!FD)\n");
       }

     else
       /* This code should never be reached.
        * If it is reached, report the bug.
        * If the assertion routine allows the program to continue,
        * abort this routine.
        */
       {
         ASSERT__BUG_DETECTED;
         return;
       }
   }




/*=r=************************************************************************/
boolean link_sim__get_pdu (DATA *pdu)
   {
     boolean        answer;
   /*------------------------------------------------------------*/
     if (m_is_slot_one_occupied)
       {
         answer = YES;
         *pdu = m_slot_one;
         m_is_slot_one_occupied = NO;
         if (m_is_slot_two_occupied)
           /* Move slot #2 occupant to slot #1 */
           {
             m__store_pdu_in_slot_one (m_slot_two);
             m_is_slot_two_occupied = NO;
           }
         usleep__microseconds (m_delay_between_pdus);
       }
     else
       answer = NO;

     if (answer && (m_corrupt != CORRUPT_NONE))
       m__corrupt_pdu (pdu);

     return (answer);
   }



/*=r=************************************************************************/
char *link_sim__current_mode (void)
   {
     static char         mode [64];
   /*------------------------------------------------------------*/
     if (m_mode == SIM_MODE_NORMAL)
       strcpy (mode, "normal");
     else
       strcpy (mode, "other than normal");
     return (mode);
   }




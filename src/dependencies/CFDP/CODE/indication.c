/* FILE: indication.c   A custom implementation of the callback
 *   routine that responds to CFDP Indications (tailored for GPM).
 * VERSION: 2.3k 2004_09_20
 * SPECS: The CFDP protocol does not specify the response to Indications.
 *   This implementation suspends transactions at the time EOF is 
 *   sent/received if the communications link is one way.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include "cfdp_code.h"




/*=r=************************************************************************/
//void indication (INDICATION_TYPE type, const TRANS_STATUS *info)
//{
//  LINK_TYPE        link_type;
//  char             request_as_string [MAX_REQUEST_STRING_LENGTH+1];
//  /*------------------------------------------------------------*/

//  link_type__get (&link_type);

//  if (((type == IND_EOF_SENT) && (link_type == LINK_OUTPUT_ONLY)) ||
//      ((type == IND_EOF_RECV) && (link_type == LINK_INPUT_ONLY)))
//    /* The Receiver cannot respond to the Sender, so suspend this trans */
//    {
//      strcpy (request_as_string, SUSPEND_REQUEST);
//      strcat (request_as_string, " ");
//      strcat (request_as_string, cfdp_trans_as_string (info->trans));
//      cfdp_give_request (request_as_string);
//    }
//}

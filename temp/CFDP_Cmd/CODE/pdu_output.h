/* pdu_output.h -- specifies routines for output of data units via comm.
 * VERSION: 2.3k 2004_09_20
 * SUMMARY:  This file specifies a module that provides output of data units
 *   via an (unspecified) lower-layer communication protocol (perhaps UDP
 *   or CCSDS command/telemetry packets).
 */

#ifndef H_PDU_OUTPUT
#define H_PDU_OUTPUT 1

#include "cfdp_code.h"


boolean pdu_output__open (ID my_id, ID partner_id);
/* WHAT IT DOES:  Attempts to perform any initialization required 
 *   to send output to the specified CFDP partner.  The caller supplies
 *   both IDs.  Returns 1 if successful; 0 otherwise.
 */

boolean pdu_output__ready (PDU_TYPE pdu_type, TRANSACTION trans, 
			   ID partner_id);
/* WHAT IT DOES:  Returns 1 if the communications path to the specified
 *   partner is ready to accept another pdu for output; otherwise, 0.
 */

void pdu_output__send (TRANSACTION trans, ID partner_id, DATA *pdu);
/* WHAT IT DOES:  If possible, sends the given pdu to the specified 
 *   CFDP partner.
 */

#endif

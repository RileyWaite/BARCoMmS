/* FILE: link_sim.h   Comm Link Simulator module spec
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 * USAGE EXAMPLE:
 *          link_sim__directive (...);
 *          link_sim__directive (...);
 *          ...
 *          link_sim__give_pdu (pdu_in);
 *          while (link_sim__get_pdu (&pdu_out))
 *             send pdu_out
 *          "free" the pdu's memory
 *          ...
 * ASSUMPTION:
 *   - The client will "free" the pdu's memory after each give/get cycle.
 */

#ifndef H_LINK_SIM
#define H_LINK_SIM 1

#include "cfdp_code.h"

#define LINK_SIM_DUPLICATE_PERCENTAGE 95
#define LINK_SIM_REORDER_PERCENTAGE 95

typedef enum { SIM_MODE_NORMAL, 
	       SIM_MODE_DUPLICATE, 
	       SIM_MODE_REORDER,
               SIM_MODE_DROP_ONE_MD, 
	       SIM_MODE_DROP_ONE_EOF, 
               SIM_MODE_DROP_ONE_FIN,
               SIM_MODE_DROP_ONE_ACK_EOF, 
	       SIM_MODE_DROP_ONE_ACK_FIN,
               SIM_MODE_DROP_ALL_BUT_MD, 
	       SIM_MODE_DROP_ALL_BUT_EOF, 
	       SIM_MODE_DROP_ALL_ACK_AND_FIN, 
               SIM_MODE_DROP_ALL_NAK, 
	       SIM_MODE_DROP_ALL_FIN,
               SIM_MODE_DROP_ALL } SIM_MODE;

typedef enum { CORRUPT_NONE, 
	       CORRUPT_EOF_CHECKSUM,
	       CORRUPT_EOF_FILE_SIZE } CORRUPT;

void link_sim__directive (char *dir);

void link_sim__give_pdu (DATA pdu);

boolean link_sim__get_pdu (DATA *pdu);

char *link_sim__current_mode (void);

#endif

#ifdef __cplusplus
extern "C"{
#endif

/* pdu_input.h -- specifies routines for input of data units via comm.
 * VERSION: 2.3k 2004_09_20
 * SUMMARY:  This file specifies a module that provides input of data units
 *   via an (unspecified) lower-layer communication protocol (perhaps UDP
 *   or CCSDS command/telemetry packets).
 */

#ifndef H_PDU_INPUT
#define H_PDU_INPUT 1

#include "cfdp_code.h"


boolean pdu_input__init (ID local_entity_id);
/* WHAT IT DOES:  Attempts to perform any initialization required 
 *   to receive input (is given the local entity-ID).  
 *   Returns 1 if successful; 0 otherwise.
 */

boolean pdu_input__connect (ID remote_entity_id);
/* WHAT IT DOES:  Attempts to initialize a connection to the specified
 *   CFDP entity.
 *   Returns 1 if successful; 0 otherwise.
 */
boolean pdu_input__poll (DATA *data_unit);
/* WHAT IT DOES:  If an incoming data_unit was received, then it returns 1
 *   (along with the data_unit); otherwise, returns 0.
 */

void comm__set_hosts_table (char *host_table_file);
/* WHAT IT DOES:  Overrides the default location for the hosts table */

#endif

#ifdef __cplusplus
}
#endif

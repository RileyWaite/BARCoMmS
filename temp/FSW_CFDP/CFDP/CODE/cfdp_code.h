#ifdef __cplusplus
extern "C"{
#endif

/* FILE: cfdp_code.h -- specs for misc routines used in a CFDP application.
 */

#ifndef H_CFDP_CODE
#define H_CFDP_CODE 1

#include "CFDP/PUB/cfdp.h"
typedef CFDP_DATA DATA;
#include "pdu_input.h"
#include "pdu_output.h"
#include "link_sim.h"
#include "link_type.h"
#include "trans_list.h"
#include "udp.h"
#include "user.h"
#include "user_input.h"
#include "usleep.h"

/* Flag indicating whether or not a transaction is in progress */
extern unsigned char transStatus;

/* Driver function for CFDP */
void main_cfdp(const char *originDir, const char *destinationDir, const char *IP, unsigned int port, int *numFiles);

/* Convert an IP address and a port to a CFDP node */
const char *toNode (const char *IP, unsigned int port, char *retNode);

/* Callback routines */
void indication (INDICATION_TYPE type, TRANS_STATUS info);

#endif

#ifdef __cplusplus
}
#endif

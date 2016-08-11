/* FILE: cfdp_code.h -- specs for misc routines used in a CFDP application.
 */

#ifndef H_CFDP_CODE
#define H_CFDP_CODE 1

#include "cfdp.h"
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

/* Callback routines */
void indication (INDICATION_TYPE type, TRANS_STATUS info);

#endif

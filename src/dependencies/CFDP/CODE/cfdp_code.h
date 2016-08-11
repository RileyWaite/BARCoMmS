#ifdef __cplusplus

extern "C"{
#endif

/* FILE: cfdp_code.h -- specs for misc routines used in a CFDP application.
 */

#ifndef H_CFDP_CODE
#define H_CFDP_CODE 1

#include "../dependencies/CFDP/PUB/cfdp.h"
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

int main_cfdp (char *id);

void m__execute_user_input (const char *user_input);

void m__show_transactions_status (void);

#endif

#ifdef __cplusplus
}
#endif

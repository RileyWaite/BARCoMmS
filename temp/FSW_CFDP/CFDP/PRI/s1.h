#ifdef __cplusplus
extern "C"{
#endif

/* FILE: s1.h   Specs for CFDP Class 1 Sender
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 * CHANGES:
 *   2007_07_31 Tim Ray
 *     - Official release.  (see pre_release_changes.log for earlier changes)
 */

#ifndef H_S1
#define H_S1 1

#include "CFDP/PUB/cfdp.h"


void s1__state_table (MACHINE *machine, int event, 
                      PDU_AS_STRUCT *pdu_in, REQUEST *req_in);
/* WHAT IT DOES:  Executes the Sender Class 2 state table logic. 
 *   i.e. given an event and a state machine, it takes the actions 
 *   prescribed in the state table.  
 * NOTES:  
 *   1) For events associated with an incoming PDU, a pointer to 
 *   the PDU's contents (expressed as a C structure) is supplied by
 *   the caller.    (otherwise, the pointer is null)
 *   2) For events associated with incoming User Requests, a pointer
 *   to the User Request is supplied by the caller.
 *   (otherwise, the pointer is null)
 */

#endif

#ifdef __cplusplus
}
#endif

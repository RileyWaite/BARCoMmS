/* FILE: trans_list.h -- specs for a module that maintains a list of
 *   CFDP transactions.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */


#ifndef H_TRANS_LIST
#define H_TRANS_LIST 1

#include "cfdp_code.h"

void trans_list__add_trans (TRANSACTION trans);
/* NOTE:  Exits the program if the list overflows. */

void trans_list__remove_trans (TRANSACTION trans);
/* NOTE:  Exits the program if the given transaction is not on the list. */

void trans_list__open_walk (void);
/* CONTEXT:  Use this to open a walk, then use 'trans_list__get_next'
 *   to step through the list one transaction at a time.
 */

boolean trans_list__get_next (TRANSACTION *trans);
/* CONTEXT:  Use 'trans_list__open_walk' to open a walk, then use
 *   this routine to step through the list one transaction at a time.
 * WHAT IT DOES:  If the walk is over (there are no more transactions)
 *   then it returns '0'.  Otherwise, returns '1', and 'trans' contains
 *   the next transaction.
 */

#endif



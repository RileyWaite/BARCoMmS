/* FILE: user_input.h  
 * VERSION: 2.3k 2004_09_20
 * SUMMARY:  This file specifies routines required to input CFDP User 
 *   Requests.
 */

#ifndef H_USER_INPUT
#define H_USER_INPUT 1

#include "cfdp_code.h"

boolean user_input__poll (char *user_input);
/* WHAT IT DOES:  If the User has supplied input, it returns '1'
 *   (and the variable 'user_input' contains the input); 
 *   otherwise, returns '0'.
 */

#endif


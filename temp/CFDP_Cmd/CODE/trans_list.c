/* FILE: trans_list.c
 * SPECS:  See trans_list.h.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include "cfdp_code.h"

#define INITIALIZE_ONCE \
   { if (!m_initialized) { m__initialize(); m_initialized = YES; } }

static boolean           m_debug = NO;
static boolean           m_initialized = NO;
static TRANSACTION       m_list [MAX_CONCURRENT_TRANSACTIONS+1];
static boolean           m_is_slot_in_use [MAX_CONCURRENT_TRANSACTIONS+1];
static int               m_walk_index;



/*=r=*************************************************************************/
static void m__initialize (void)
{
  int             i;
  /*------------------------------------------------------------*/

  for (i=0; i<=MAX_CONCURRENT_TRANSACTIONS; i++)
    m_is_slot_in_use[i] = NO;

  m_walk_index = 0;
}




/*=r=*************************************************************************/
void trans_list__add_trans (TRANSACTION trans)
{
  int          i;
  boolean      success;
  /*------------------------------------------------------------*/

  INITIALIZE_ONCE;

  success = NO;
  for (i=0; i<MAX_CONCURRENT_TRANSACTIONS; i++)
    if (!m_is_slot_in_use[i])
      {
	success = YES;
	m_list[i] = trans;
	m_is_slot_in_use[i] = YES;
	if (m_debug)
	  msg__ ("trans_list__add_trans:  using slot #%u.\n", i);
	break;
      }
  
  if (!success)
    {
      msg__ ("<FATAL> trans_list overflowed!\n");
      exit (1);
    }
}



/*=r=*************************************************************************/
void trans_list__remove_trans (TRANSACTION trans)
{
  int          i;
  boolean      success;
  /*------------------------------------------------------------*/

  INITIALIZE_ONCE;

  success = NO;
  for (i=0; i<MAX_CONCURRENT_TRANSACTIONS; i++)
    if ((m_is_slot_in_use[i]) && 
	(cfdp_are_these_trans_equal (m_list[i], trans)))
      {
	success = YES;
	m_is_slot_in_use[i] = NO;
	if (m_debug)
	  msg__ ("trans_list__remove_trans:  using slot #%u.\n", i);
	break;
      }
  
  if (!success)
    {
      msg__ ("<FATAL> trans_list removal failure.\n");
      exit (1);
    }
}



/*=r=*************************************************************************/
void trans_list__open_walk (void)
{
  /*------------------------------------------------------------*/

  INITIALIZE_ONCE;

  m_walk_index = 0;
}



/*=r=*************************************************************************/
boolean trans_list__get_next (TRANSACTION *trans)
{
  boolean         success;
  /*------------------------------------------------------------*/

  INITIALIZE_ONCE;

  success = NO;
  for ( ; m_walk_index<MAX_CONCURRENT_TRANSACTIONS; m_walk_index++)
    {
      if (m_is_slot_in_use[m_walk_index])
	{
	  success = YES;
	  *trans = m_list[m_walk_index];
	  if (m_debug)
	    msg__ ("trans_list__get_next:  using slot #%u.\n", m_walk_index);
	  break;
	}
    }
  
  /* Careful - must increment walk-index to avoid infinite loop) */
  m_walk_index ++;

  return (success);
}

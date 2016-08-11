/* FILE: link_type.c 
 * VERSION: 2.3k 2004_09_20
 * SPECS:  See link_type.h.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include "cfdp_code.h"

static LINK_TYPE               m_link_type = LINK_NONE;



/*=r=************************************************************************/
void link_type__set (LINK_TYPE link_type)
{
  /*------------------------------------------------------------*/
  if (link_type == LINK_TWO_WAY)
    msg__ ("<Link_Type> We now have a two-way link.\n");
  else if (link_type == LINK_INPUT_ONLY)
    msg__ ("<Link_Type> We now have a one-way link (input only).\n");
  else if (link_type == LINK_OUTPUT_ONLY)
    msg__ ("<Link_Type> We now have a one-way link (output only).\n");
  else if (link_type == LINK_NONE)
    msg__ ("<Link_Type> We are now between passes (no link).\n");
  else
    {
      msg__ ("<ERROR> <%s/%u> Invalid link-type (#%u).\n",
             __FILE__, __LINE__, link_type);
      return;
    }
  
  m_link_type = link_type;
}



/*=r=************************************************************************/
void link_type__get (LINK_TYPE *link_type)
{
  /*------------------------------------------------------------*/
  *link_type = m_link_type;
}

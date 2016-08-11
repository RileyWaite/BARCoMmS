#ifdef __cplusplus
extern "C"{
#endif

/* FILE: link_type.h -- specs for module that maintains a link type.
 * VERSION: 2.3k 2004_09_20
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#ifndef H_LINK_TYPE
#define H_LINK_TYPE 1

typedef enum 
{ LINK_TWO_WAY,       /* Normal (2-way) pass */      
  LINK_INPUT_ONLY,    /* We can receive, but can't send */
  LINK_OUTPUT_ONLY,   /* We can send, but can't receive */
  LINK_NONE           /* Between passes */
} LINK_TYPE;

void link_type__set (LINK_TYPE link_type);
/* WHAT IT DOES:  Allows the caller to indicate the beginning and end 
 *   of contacts (aka passes).  
 * EXAMPLES:
 *     link_type__set (LINK_TWO_WAY);     // start of 2-way pass
 *     link_type__set (LINK_NONE);        // end of pass
 *     link_type__set (LINK_OUTPUT_ONLY); // start of 1-way pass
 *     link_type__set (LINK_TWO_WAY);     // switch to 2-way
 */

void link_type__get (LINK_TYPE *link_type);
/* WHAT IT DOES:  The current 'link-type' is returned to the caller. */

#endif

#ifdef __cplusplus
}
#endif

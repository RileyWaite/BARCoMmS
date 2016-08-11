#ifdef __cplusplus

extern "C"{
#endif

/* FILE: message_class.h -- specs for a module that maintains message 
 *   filter settings (i.e. "which classes of messages are currently enabled
 *   for output?).
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 * SUMMARY:  The CFDP library user chooses compile-time settings of these
 *   filters.  The compile-time settings can be overridden at run-time.
 * CHANGES:
 *   2007_12_05 Tim Ray (TR)
 *     - Initial release with version 3.0d
 */

#ifndef H_MESSAGE_CLASS
#define H_MESSAGE_CLASS 1

#include "../dependencies/CFDP/PUB/cfdp.h"

/* (Message classes are defined in PUB/cfdp_provides.h) */

#define NUMBER_OF_MESSAGE_CLASSES 10

boolean message_class__enabled (int message_class);
/* WHAT IT DOES:  Returns '1' if the given message-class is enabled;
 *   otherwise, '0'.  
 */

boolean message_class__enable (int message_class);
/* WHAT IT DOES:  If the given message-class is recognized, the message-
 *   class is enabled and the return status is '1'.  Otherwise, no action
 *   is taken and the return status is '0'.
 * NOTE:  If the given class is 0, then all message classes are enabled.
 */

boolean message_class__disable (int message_class);
/* WHAT IT DOES:  If the given message-class is recognized, the message-
 *   class is disabled and the return status is '1'.  Otherwise, no action
 *   is taken and the return status is '0'.
 * NOTE:  If the given class is 0, then all message classes are disabled.
 */

#endif

#ifdef __cplusplus
}
#endif

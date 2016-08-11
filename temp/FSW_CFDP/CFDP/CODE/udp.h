#ifdef __cplusplus
extern "C"{
#endif

/* FILE: udp.h  --  first (simplest) cut.
 * VERSION: 2.3k 2004_09_20
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 * ASSUMPTIONS/LIMITATIONS:
 *   - Only one socket can be created (and used for input).
 *   - Only one partner (actually, input can come from anywhere, but all
 *     output goes to the chosen partner).
 *   - Messages are either null-terminated strings or length/value data.
 *   - Incoming messages (datagrams) are not to exceed max_datagram_length
 *     bytes.
 *   - Program is exited if an error occurs.
 * USAGE:
 *   Always call udp--open and udp--choose_partner before performing i/o.
 */

#ifndef H_UDP
#define H_UDP 1

#include "cfdp_code.h"

#define  MAX_DATAGRAM_LENGTH  (MAX_PDU_LENGTH + 20)
#define  MAX_PORT_NUMBER  5000
#define  MIN_PORT_NUMBER  1024


boolean udp__open (int port_number);
/* WHAT IT DOES:  Attempts to create a socket on localhost for the given 
 *   port number.  If successful, returns 1; else 0.
 */

void udp__choose_partner (char *ip_address, int port_number);
/* WHAT IT DOES:  Initializes the data structures needed for communicating
 *   with the partner socket.  
 */


void udp__write_data (DATA message_out);
/* WHAT IT DOES:  Sends the given data to the partner socket. */

void udp__write_string (char *message_out);
/* WHAT IT DOES:  Sends the given null-terminated string to the partner. */


boolean udp__read_data_with_timeout (int timeout_in_milliseconds, 
                                     DATA *message_in);

boolean udp__read_string_with_timeout (int timeout_in_milliseconds, 
                                       char *message_in);

#endif

#ifdef __cplusplus
}
#endif

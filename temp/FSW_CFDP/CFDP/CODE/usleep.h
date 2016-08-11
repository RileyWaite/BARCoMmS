#ifdef __cplusplus
extern "C"{
#endif

/* FILE: usleep.h -- specs for module that does sub-second sleeps.
 * VERSION: 2.3k 2004_09_20
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#ifndef H_USLEEP
#define H_USLEEP 1

void usleep__milliseconds (int how_many);

void usleep__microseconds (u_int_4 how_many);

#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"{
#endif

/* FILE: user.h -- specs for a CFDP User module
 * VERSION: 2.3k 2004_09_20
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */


#ifndef H_USER
#define H_USER 1

void msg__ (const char *format, ...);
void d_msg__ (const char *format, ...);
void i_msg__ (const char *format, ...);
void w_msg__ (const char *format, ...);
void e_msg__ (const char *format, ...);

#endif

#ifdef __cplusplus
}
#endif

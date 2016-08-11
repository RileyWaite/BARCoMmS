#ifdef __cplusplus
extern "C"{
#endif

/* FILE:  test_cfdp.h -- specs for a program to support regression testing of 
 *   my CFDP implementation.
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#ifndef H_TEST_CFDP

/* Transactions create temporary files using these patterns */
#define FILENAME_PREFIX_FOR_SOURCE "src"
#define FILENAME_PREFIX_FOR_DESTINATION "dest"
#define FILENAME_SUFFIX_FOR_SOURCE ".tmp"
#define FILENAME_SUFFIX_FOR_DESTINATION ".tmp"

/* For each transaction, a temporary source file is created (with random
 * contents).  This is the default size for source files 
 */
#define DEFAULT_SOURCE_FILE_SIZE 100000

/* The program recognizes an input line as a comment if the first char is */
#define COMMENT_STARTS_WITH_THIS_CHAR '!'

/* Next def specifies the filename for sending a message to a CFDP node */
/* For example, if node-id is "23", then replace %s with "23" */
#define GENERIC_FILENAME_TO_NODE "cfdp_%s.in"   

/* Next def specifies the filename for receiving a message from a CFDP node */
/* If node-id is "23", then replace %s with "23" */
#define GENERIC_FILENAME_FROM_NODE "cfdp_%s.out"   

#define MAX_FILENAME_LENGTH 32
#define MAX_DIRECTIVE_LENGTH 80   
#define MAX_ID_LENGTH 32
#define MAX_LINE_LENGTH 80
#define MAX_NODES 2   /* Max CFDP nodes that can be tested at one time */

/* I have experienced some pipe i/o errors if delay is not sufficient */
#define DELAY_BETWEEN_MSGS_IN_MILLISECS 500

/* This is the command that deletes a file from disk */
#define OS_SYNTAX_FOR_DELETING_A_FILE "rm --force %s"

#define H_TEST_CFDP 1
#endif

#ifdef __cplusplus
}
#endif

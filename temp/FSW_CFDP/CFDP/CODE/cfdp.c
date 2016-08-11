/* For time_t and stat */
#include <sys/types.h>
#include <sys/stat.h>

/* For scandir */
#include <dirent.h>

#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <signal.h>
#include "cfdp_code.h"
#include "time.h"

#define MY_DEFAULT_NODE "23"
#define  NO  0
#define  YES  1

/* Flag indicating a transaction's current status
 * 0 - Transaction is in progress
 * 1 - Transaction was successful
 * 2 - Transaction was abandoned
 * 3 - Transaction was cancelled
 * 4 - Transaction failed (metadata was not received)
 * 5 - Transaction status is unkown
 * 6 - Transaction status is unrecognized
*/
unsigned char transStatus = 1;

/* Name of the file being sent */
static char fileBeingSent[512];

/* Copy of the origin directory for use in timesortasc and timesortdesc */
static char dir[512];

static time_t get_mtime(const char *path){
    struct stat statbuf;

    if(stat(path, &statbuf) == -1){
        perror(path);
        exit(1);
    }

    return statbuf.st_mtime;
}

/* Sort files based on last modification time in descending order */
static int timesortdesc(const struct dirent **d1, const struct dirent **d2){
    char fullFile1[512];
    strcpy(fullFile1, dir);
    strcat(fullFile1, "/");
    strcat(fullFile1, d1[0]->d_name);

    char fullFile2[512];
    strcpy(fullFile2, dir);
    strcat(fullFile2, "/");
    strcat(fullFile2, d2[0]->d_name);

    long int time1 = get_mtime(fullFile1);
    long int time2 = get_mtime(fullFile2);

    if(time1 < time2){
        return 1;
    }
    else if(time1 > time2){
        return -1;
    }
    else if(time1 == time2){
        return 0;
    }

    /* Note: There is no return value resserved to indicate an error.
     * An application wishing to check for error situations should set errno to 0, then call timesort(), then check errno.
     */
}

/* Sort files based on last modification time in ascending order */
static int timesortasc(const struct dirent **d1, const struct dirent **d2){
    char fullFile1[512];
    strcpy(fullFile1, dir);
    strcat(fullFile1, "/");
    strcat(fullFile1, d1[0]->d_name);

    char fullFile2[512];
    strcpy(fullFile2, dir);
    strcat(fullFile2, "/");
    strcat(fullFile2, d2[0]->d_name);

    long int time1 = get_mtime(fullFile1);
    long int time2 = get_mtime(fullFile2);

    if(time1 > time2){
        return 1;
    }
    else if(time1 < time2){
        return -1;
    }
    else if(time1 == time2){
        return 0;
    }

    /* Note: There is no return value resserved to indicate an error.
     * An application wishing to check for error situations should set errno to 0, then call timesort(), then check errno.
     */
}

static void put(const char *fullFile, const char *node, const char *destinationDir, const char *file){
    char request[1024];

    strcpy(request, "put ");
    strcat(request, fullFile);
    strcat(request, " ");
    strcat(request, node);
    strcat(request, " ");
    strcat(request, destinationDir);
    strcat(request, "/");
    strcat(request, file);

    cfdp_give_request(request);
}

static int directoryUpdated(const char *originDir, const char *destinationDir, const char *IP, unsigned int port, int *numFiles){
    struct dirent **entryList;
    int count = scandir(originDir, &entryList, 0, timesortdesc);
    int badCount = 0;

    /* Return if scandir returned -1 (error) */
    if(count < 0){
        return count;
    }

    for(int i = 0; i < count; ++i){
        struct dirent *entry;
        entry = entryList[i];

        /* Ignore files starting with '.' */
        if(entry->d_name[0] == '.'){
            badCount++;
            if(count - badCount == 0){
                exit(1);
            }
            continue;
        }

        /* check if a transaction is in progress
         * if not, put a file from the directory
         * else, continue
         */
        if(transStatus != 0){
            if((*numFiles) != 0){
                /* Temp string for storing node value associated with IP/port */
                char node[132];

                /* Construct full file path */
                char fullFile[512];
                strcpy(fullFile, originDir);
                strcat(fullFile, "/");
                strcat(fullFile, entry->d_name);

                put(fullFile, toNode(IP, port, node), destinationDir, entry->d_name);
                strcpy(fileBeingSent, fullFile);
                (*numFiles)--;
            }
            else{
                exit(1);
            }
        }

        free(entry);
    }

    free(entryList);

    return count;
}

static void handleTransactions(const char *originDir, const char *destinationDir, const char *IP, unsigned int port, int *numFiles){
    boolean any_input;
    DATA pdu;

    for(;;){
        any_input = NO;

        directoryUpdated(originDir, destinationDir, IP, port, numFiles);

        if (pdu_input__poll(&pdu)){
            any_input = YES;
            cfdp_give_pdu(pdu);
        }

        if (!any_input){
            /* Cycle each transaction.  This includes deleting any
            * transactions that have completed, and giving each trans the
            * chance to make progress (check for expired timers, etc).
            */
            cfdp_cycle_each_transaction();
            usleep__microseconds(1);
            fflush(stdout);
        }

        if(transStatus == 1){
            remove(fileBeingSent);
        }
        else if(transStatus == 0){
            continue;
        }
        else{
            exit(1);
        }
    }
}

void cfdp (const char *originDir, const char *destinationDir, const char *IP, unsigned int port, int *numFiles){
    ID          my_entity_id;
    char        my_entity_id_as_string[128];
    /*------------------------------------------------------------*/

    /* Register callback routines */
    register_indication(indication);
    register_pdu_output_open(pdu_output__open);
    register_pdu_output_ready(pdu_output__ready);
    register_pdu_output_send(pdu_output__send);

    /* Initialize the link sim */
    char sim[32] = "success_rate=100";
    link_sim__directive(sim);
    strcpy(sim, "delay_between_pdus=0");
    link_sim__directive(sim);
    strcpy(sim, "normal");
    link_sim__directive(sim);
    strcpy(sim, "corrupt_none");
    link_sim__directive(sim);

    /* Initialize the message classes */
    cfdp_enable_message_class(CFDP_MSG_INDICATIONS);
    cfdp_disable_message_class(CFDP_MSG_DEBUG_MEMORY_USE);
    cfdp_disable_message_class(CFDP_MSG_DEBUG_NAK);
    cfdp_disable_message_class(CFDP_MSG_DEBUG_PDU);
    cfdp_disable_message_class(CFDP_MSG_PDU_FILEDATA);
    cfdp_enable_message_class(CFDP_MSG_PDU_NON_FILEDATA);
    cfdp_disable_message_class(CFDP_MSG_PDU_RETRANSMITTED_FD);
    cfdp_disable_message_class(CFDP_MSG_STATE_ALL);
    cfdp_disable_message_class(CFDP_MSG_STATE_CHANGE);

    /* Initialize the MIB */
    cfdp_set_mib_parameter(MIB_ISSUE_EOF_RECV, "yes");
    cfdp_set_mib_parameter(MIB_ISSUE_EOF_SENT, "yes");
    cfdp_set_mib_parameter(MIB_ISSUE_FILE_SEGMENT_RECV, "no");
    cfdp_set_mib_parameter(MIB_ISSUE_FILE_SEGMENT_SENT, "no");
    cfdp_set_mib_parameter(MIB_ISSUE_RESUMED, "yes");
    cfdp_set_mib_parameter(MIB_ISSUE_SUSPENDED, "yes");
    cfdp_set_mib_parameter(MIB_ISSUE_TRANSACTION_FINISHED, "yes");
    cfdp_set_mib_parameter(MIB_ACK_LIMIT, "25");
    cfdp_set_mib_parameter(MIB_ACK_TIMEOUT, "5");
    cfdp_set_mib_parameter(MIB_INACTIVITY_TIMEOUT, "86400");
    cfdp_set_mib_parameter(MIB_NAK_LIMIT, "25");
    cfdp_set_mib_parameter(MIB_NAK_TIMEOUT, "5");
    cfdp_set_mib_parameter(MIB_SAVE_INCOMPLETE_FILES, "no");
    cfdp_set_mib_parameter(MIB_OUTGOING_FILE_CHUNK_SIZE, "250");

    /* Determine my entity-id */
    strcpy(my_entity_id_as_string, MY_DEFAULT_NODE);

    /* Initialize my entity-id */
    cfdp_set_mib_parameter(MIB_MY_ID, my_entity_id_as_string);

    /* Validate my entity-id */
    if (!cfdp_id_from_string(my_entity_id_as_string, &my_entity_id)){
        msg__("<ERROR> My ID (%s) is invalid.\n", my_entity_id_as_string);
        return;
    }

    if (!pdu_input__init(my_entity_id)){
        msg__ ("<FATAL>  Unable to initialize my comm port.\n");
        return;
    }

    link_type__set(LINK_TWO_WAY);

    /* Handle all CFDP transactions */
    handleTransactions(originDir, destinationDir, IP, port, numFiles);
}

/* WHAT IT DOES:  ALlows us to be aware of a lost pipe.  (Exits). */
void m__sigpipe_handler(int signal){
    char           msg[128];
    /*------------------------------------------------------------*/

    system("date");
    strcpy(msg, "<FATAL> SIGPIPE signal received.\n");
    msg__("%s", msg);
    fflush(stdout);
    exit(1);
}

void main_cfdp(const char *originDir, const char *destinationDir, const char *IP, unsigned int port, int *numFiles){
    struct sigaction      new_action;
    struct sigaction      old_action;
    /*------------------------------------------------------------*/

    /* Catch the SIGPIPE signal */
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    new_action.sa_handler = m__sigpipe_handler;
    if(sigaction (SIGPIPE, &new_action, &old_action) != 0){
        msg__("<FATAL> Unable to register SIGPIPE signal-handler.\n");
        exit(1);
    }

    /* Copy originDir to dir for use in timesortasc and timesortdesc */
    strcpy(dir, originDir);

    cfdp(originDir, destinationDir, IP, port, numFiles);
}

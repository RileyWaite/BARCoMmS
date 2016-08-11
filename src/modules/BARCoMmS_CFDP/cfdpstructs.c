#include "cfdpstructs.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

// Default MIB parameters for the case where init file fails to read
MIB global_mib = {"Yes", "Yes", "No", "No", "23", "Yes", "No", "Yes", "Yes", 25, 5, 65200, 86400, 25, 5};

// Default MessageClasses parameters for the case where init file fails to read
MessageClasses global_messageClasses = {0, 1, 0, 0, 0, 0, 1, 0, 0, 0};

// Default LinkSim parameters for the case where init file fails to read
LinkSim global_linkSim = {100, 0, "sim normal", "sim corrupt_none"};

// Convert a string to all lowercase
char *toLower(char *str){
    for(unsigned int i = 0; i < strlen(str); ++i){
      str[i] = tolower(str[i]);
    }

    return str;
}

// Allow case insensitive values as well as boolean values for 'Yes'/'No' parameters
char *toYesNo(char *str){
    if(!strcmp(str, "1") || !strcmp(toLower(str), "yes")){
        strcpy(str, "Yes");
    }
    else if(!strcmp(str, "0") || !strcmp(toLower(str), "no")){
        strcpy(str, "No");
    }
    else{
        // Default to 'No' if invalid value is entered
        strcpy(str, "No");
    }

    return str;
}

// Allow case insensitive 'Yes'/'No' values as well as boolean values for boolean parameters
unsigned char toBoolean(char *str){
    if(!strcmp(str, "1") || !strcmp(toLower(str), "yes")){
        strcpy(str, "1");
        return 1;
    }
    else if(!strcmp(str, "0") || !strcmp(toLower(str), "no")){
        strcpy(str, "0");
        return 0;
    }
    else{
        // Default to 0 if invalid value is entered
        return 0;
    }
}

// Append a single character to a string
int append(char *str, unsigned short size, char c){
     if(strlen(str) + 1 >= size){
          return 1;
     }

     int len = strlen(str);
     str[len] = c;
     str[len+1] = '\0';

     return 0;
}

// Extract the value associated with a parameter
char *extractVal(char *line, char *result){
    memset(result, 0, sizeof(char));

    unsigned short i;
    for(i = 0; i < strlen(line); ++i){
        if(line[i] == ':' || line[i] == '?'){
            if(i < strlen(line) - 2){
                i += 2;
            }
            break;
        }
    }
    while(i < strlen(line) && line[i] != '\n'){
        append(result, strlen(line), line[i]);
        ++i;
    }

    return result;
}

// Initialize the MIB, MessageClasses, and LinkSim structs
void initStructs(){
    char line[255];
    char result[255];

    FILE *fp = fopen("resources/BARCoMmS_CFDP.init", "r");

    if(fp != NULL){
        while(fgets(line, sizeof(line), fp)){
            // For MIB parameters
            if(strstr(line, "Issue EOF-Sent Indication?")){
                strcpy(global_mib.EOFSent, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue EOF-Received Indication?")){
                strcpy(global_mib.EOFRecv, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue File-Segment-Sent Indication?")){
                strcpy(global_mib.fileSent, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue File-Segment-Received Indication?")){
                strcpy(global_mib.fileRecv, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue Resumed Indication?")){
                strcpy(global_mib.resumed, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue Suspended Indication?")){
                strcpy(global_mib.suspended, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Issue Transaction-Finished Indication?")){
                strcpy(global_mib.transFin, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "Save Incomplete Files?")){
                strcpy(global_mib.save, toYesNo(extractVal(line, result)));
            }
            if(strstr(line, "ACK Limit:")){
                global_mib.ACKLimit = atoi(extractVal(line, result));
            }
            if(strstr(line, "ACK Timeout:")){
                global_mib.ACKTimeout = atoi(extractVal(line, result));
            }
            if(strstr(line, "NAK Limit:")){
                global_mib.NAKLimit = atoi(extractVal(line, result));
            }
            if(strstr(line, "NAK Timeout:")){
                global_mib.NAKTimeout = atoi(extractVal(line, result));
            }
            if(strstr(line, "Inactivity Timeout:")){
                global_mib.inactivity = atoi(extractVal(line, result));
            }
            if(strstr(line, "Outgoing File Chunk Size (Bytes): ")){
                extractVal(line, result);

                if(atoi(result) < 4){
                    global_mib.chunkSize = 4;
                }
                else{
                    global_mib.chunkSize = atoi(result);
                }
            }
            if(strstr(line, "Node ID:")){
                extractVal(line, result);

                if(strlen(result) < 8){
                    strcpy(global_mib.ID, result);
                }
                else{
                     strcpy(global_mib.ID, "23");
                }
            }

            // For MessageClasses parameters
            if(strstr(line, "Indications:")){
                global_messageClasses.indications = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "Debug Memory Use:")){
                global_messageClasses.debugMemoryUse = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "Debug NAK:")){
                global_messageClasses.debugNAK = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "Debug PDU:")){
                global_messageClasses.debugPDU = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "PDU Filedata:")){
                global_messageClasses.PDUFiledata = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "PDU Non-Filedata:")){
                global_messageClasses.PDUNonFiledata = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "PDU Retransmitted FD:")){
                global_messageClasses.PDURetransmittedFD = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "State All: ")){
                global_messageClasses.stateAll = toBoolean(extractVal(line, result));
            }
            if(strstr(line, "State Change:")){
                global_messageClasses.stateChange = toBoolean(extractVal(line, result));
            }

            // For LinkSim parameters
            if(strstr(line, "Success Rate (%):")){
                global_linkSim.rate = atoi(extractVal(line, result));
            }
            if(strstr(line, "Delay Between PDUs (milliseconds):")){
                global_linkSim.delay = atoi(extractVal(line, result));
            }
            if(strstr(line, "Mode:")){
                strcpy(global_linkSim.mode, toLower(extractVal(line, result)));
                if(strcmp(global_linkSim.mode, "sim normal") && strcmp(global_linkSim.mode, "sim duplicate") && strcmp(global_linkSim.mode, "sim reorder") &&
                        strcmp(global_linkSim.mode, "sim drop_one_md") && strcmp(global_linkSim.mode, "sim drop_one_eof") && strcmp(global_linkSim.mode, "sim drop_one_fin") &&
                        strcmp(global_linkSim.mode, "sim drop_one_ack_eof") && strcmp(global_linkSim.mode, "sim drop_one_ack_fin") && strcmp(global_linkSim.mode, "sim drop_all_but_eof") &&
                        strcmp(global_linkSim.mode, "sim drop_all_but_md") && strcmp(global_linkSim.mode, "sim drop_all_ack_and_fin") && strcmp(global_linkSim.mode, "sim drop_all_nak") &&
                        strcmp(global_linkSim.mode, "sim drop_all_fin") && strcmp(global_linkSim.mode, "sim drop_all")){
                    strcpy(global_linkSim.mode, "sim normal");
                }
            }
            if(strstr(line, "Corruption:")){
                strcpy(global_linkSim.corruption, toLower(extractVal(line, result)));
                if(strcmp(global_linkSim.corruption, "sim corrupt_none") && strcmp(global_linkSim.corruption, "sim corrupt_eof_checksum") && strcmp(global_linkSim.corruption, "sim corrupt_eof_file_size")){
                    strcpy(global_linkSim.corruption, "sim corrupt_none");
                }
            }
        }

        memset(line, 0, sizeof(char));
        memset(result, 0, sizeof(char));

        fclose(fp);
    }
}

#ifdef __cplusplus
extern "C"{
#endif

#ifndef CFDPSTRUCTS_H
#define CFDPSTRUCTS_H

#include <stdbool.h>

// For MIB 'Yes'/'No' values
#define CHOICE_SIZE 4

// For MIB node value
#define NODE_SIZE 8

// For LinkSim mode and corruption values
#define SIM_MODE_SIZE 32

// For initializing MIB settings
struct MIB{
    char EOFRecv[CHOICE_SIZE];
    char EOFSent[CHOICE_SIZE];
    char fileRecv[CHOICE_SIZE];
    char fileSent[CHOICE_SIZE];
    char ID[NODE_SIZE];
    char resumed[CHOICE_SIZE];
    char save[CHOICE_SIZE];
    char suspended[CHOICE_SIZE];
    char transFin[CHOICE_SIZE];
    unsigned int ACKLimit;
    unsigned int ACKTimeout;
    unsigned int chunkSize;
    unsigned int inactivity;
    unsigned int NAKLimit;
    unsigned int NAKTimeout;
};

// For initializing message class settings
struct MessageClasses{
    bool all;
    bool indications;
    bool debugMemoryUse;
    bool debugNAK;
    bool debugPDU;
    bool PDUFiledata;
    bool PDUNonFiledata;
    bool PDURetransmittedFD;
    bool stateAll;
    bool stateChange;
};

// For initializing link sim settings
struct LinkSim{
    unsigned int rate;
    unsigned int delay;
    char mode[SIM_MODE_SIZE];
    char corruption[SIM_MODE_SIZE];
};

// Typedefs
typedef struct MIB MIB;
typedef struct MessageClasses MessageClasses;
typedef struct LinkSim LinkSim;

// Global instances of each struct
extern MIB global_mib;
extern MessageClasses global_messageClasses;
extern LinkSim global_linkSim;

// For converting a string to all lowercase
char *toLower(char *str);

// For allowing case insensitive values as well as boolean values for 'Yes'/'No' parameters
char *toYesNo(char *str);

// For allowing case insensitive 'Yes'/'No' values as well as boolean values for boolean parameters
unsigned char toBoolean(char *str);

// For appending a single character to a string
int append(char *str, unsigned short size, char c);

// For initializing structs
void initStructs();

// For extracting the value associated with a parameter
char *extractVal(char *line, char *result);

#endif // CFDPSTRUCTS_H

#ifdef __cplusplus
}
#endif

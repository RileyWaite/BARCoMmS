#include "CFDP/CODE/cfdp_code.h"

int main(int argc, char *argv[])
{
    if(argc != 6){
        printf("Error: Six command line arguments required:\n./FSW_CFDP /origin/dir /destination/dir recv_IP recv_port num_files_to_send\n");
        return 1;
    }

    /* Directory where files will be sent from */
    const char *originDir = argv[1];

    /* Directory where files will be delivered */
    const char *destinationDir = argv[2];

    /* Receiver's node */
    const char *IP = argv[3];

    /* Receiver's port */
    unsigned int port = atoi(argv[4]);

    /* Number of files to be sent (-1 for all files in originDir) */
    int numFiles = atoi(argv[5]);

    main_cfdp(originDir, destinationDir, IP, port, &numFiles);
}

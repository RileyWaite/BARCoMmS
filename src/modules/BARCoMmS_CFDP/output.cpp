#include "output.h"

// Emit a signal to BARCoMmS_CFDP to output CFDP messages to plainTextEdit_output
void Output::printer(char *str){
    emit output_appendOutput(str);
}

// For output from CFDP to Command_output
Output *outputSender = new Output();

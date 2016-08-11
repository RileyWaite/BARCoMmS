#include "worker.h"

// Check for incoming PDUs on a separate worker thread
void Worker::run(){
    this->end = 0;
    DATA pdu;

    for(;;){
        // Terminate the thread if the window closes
        if(this->end == 1){
            break;
        }

        bool any_input = 0;

        if(pdu_input__poll(&pdu)){
            any_input = 1;
            emit readyToGivePDU(pdu);
        }

        if(!any_input){
            /* Cycle each transaction.  This includes deleting any
             * transactions that have completed, and giving each trans the
             * chance to make progress (check for expired timers, etc).
             */
            emit readyToCycleTransactions();
            usleep__microseconds(1);
        }
    }

    this->quit();
}

// Flag to tell the worker thread that its work is done
void Worker::terminate(){
    end = 1;
}

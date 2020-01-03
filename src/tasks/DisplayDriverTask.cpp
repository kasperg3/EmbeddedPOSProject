//
// Created by kasper on 10/24/19.
//

#include <thread>
#include "DisplayDriverTask.hpp"
#include "../utilities/queue.h"


void DisplayDriverTask::setMessageQueue(std::string msg) {
    message_queue_descriptor = msg;
}

void *DisplayDriverTask::taskHandler(DisplayDriverTask *displayDriver) {
    //displayDriver->init();
    //displayDriver->clear();
    /* Initialize the queue attributes */
    mq_unlink(QUEUE_LCD);
    Queue receiptQueue(QUEUE_RECEIPT,O_RDONLY|O_CREAT,QUEUE_RECEIPT_MAXMSG,QUEUE_RECEIPT_MSGSIZE);
    while(true) {
        std::string buffer = receiptQueue.receive();
        if(buffer[0] == '1'){
            //Remove the first character of the message
            buffer.erase(0,1);
            buffer.erase(buffer.size()-1);
            displayDriver->print(40,buffer);
        }else if(buffer[0] == '0'){
            buffer.erase(0,1);
            buffer.erase(buffer.size()-1);
            displayDriver->print(0,buffer);
        }

        printf("[DisplayDriver]: Received message: %s \n", buffer.c_str());
        fflush(stdout);
    }

    /* Cleanup */
    printf("[CONSUMER]: Cleanup...\n");
    mq_unlink(QUEUE_LCD);

}

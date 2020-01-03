//
// Created by kasper on 10/24/19.
//

#include "NumpadDriverTask.hpp"
#include "../utilities/queue.h"

void NumpadDriverTask::setMessageQueue(std::string msg) {
    message_queue_descriptor = msg;
}

void *NumpadDriverTask::taskHandler(NumpadDriverTask *numpadDriver) {
    mq_unlink(QUEUE_NUMPAD);

    Queue queue(QUEUE_NUMPAD, O_CREAT | O_WRONLY, QUEUE_CARDREADER_MAXMSG, QUEUE_CARDREADER_MSGSIZE);
    int value = -1;
    char buffer[QUEUE_NUMPAD_MSGSIZE] = "";
    while(th_publisher_running) {
        value = numpadDriver->check();
        if(value != -1){
            buffer[0] = value;
            queue.send(buffer);
            printf("[PUBLISHER]: Sending message %c ...\n", value);
            usleep(300000); //Sleep to avoid getting multiple values
        }
        fflush(stdout);
    }

    /* Cleanup */
    printf("[PUBLISHER]: Cleanup...\n");
    mq_unlink(QUEUE_NUMPAD);

    return nullptr;
}
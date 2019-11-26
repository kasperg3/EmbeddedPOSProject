//
// Created by kasper on 10/24/19.
//

#include "NumpadDriverTask.hpp"

void NumpadDriverTask::setMessageQueue(std::string msg) {
    message_queue_descriptor = msg;
}



void *NumpadDriverTask::taskHandler(NumpadDriverTask *numpadDriver) {
    //Init numpaddriver
    //numpadDriver->init();

    /* Open the created queue by the consumer. */
    mqd_t mq;
    do {
        mq = mq_open(QUEUE_NAME, O_WRONLY);
        if(mq < 0) {
            printf("[PUBLISHER]: The queue is not created yet. Waiting...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(mq == -1);

    printf("[PUBLISHER]: Queue opened, queue descriptor: %d.\n", mq);

    //int value;
    int value = -1;
    char buffer[QUEUE_MSGSIZE] = "";
    while(th_publisher_running) {
        value = numpadDriver->check();// displayDriver.print(1, value + '0');
        if(value != -1){
            buffer[0] = (char)value + '0';
            printf("[PUBLISHER]: Sending message %i ...\n", value);
            mq_send(mq, buffer, QUEUE_MSGSIZE, 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        fflush(stdout);
    }



    /* Cleanup */
    printf("[PUBLISHER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return nullptr;
}
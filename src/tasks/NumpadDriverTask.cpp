//
// Created by kasper on 10/24/19.
//

#include "NumpadDriverTask.hpp"

void NumpadDriverTask::setMessageQueue(std::string msg) {
    message_queue_descriptor = msg;
}

void *NumpadDriverTask::taskHandler(NumpadDriverTask *numpadDriver) {
    mq_unlink(QUEUE_NUMPAD);
    /* Open the created queue by the consumer. */
    mqd_t mq;
    do {
        mq = mq_open(QUEUE_NUMPAD, O_WRONLY);
        if(mq < 0) {
            printf("[PUBLISHER]: The queue is not created yet. Waiting...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(mq == -1);

    printf("[PUBLISHER]: Queue opened, queue descriptor: %d.\n", mq);

    //int value;
    int value = -1;
    char buffer[QUEUE_NUMPAD_MSGSIZE] = "";
    while(th_publisher_running) {
        value = numpadDriver->check();
        if(value != -1){
            buffer[0] = (char)value;
            printf("[PUBLISHER]: Sending message %c ...\n", value);
            mq_send(mq, buffer, QUEUE_NUMPAD_MSGSIZE, 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        fflush(stdout);
    }

    /* Cleanup */
    printf("[PUBLISHER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NUMPAD);

    return nullptr;
}
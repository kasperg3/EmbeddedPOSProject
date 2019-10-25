//
// Created by kasper on 10/24/19.
//

#include "../include/DisplayDriverTask.h"


void DisplayDriverTask::setMessageQueue(std::string msg) {
    message_queue_descriptor = msg;
}

void *DisplayDriverTask::taskHandler(DisplayDriverTask *displayDriver) {
    //((DisplayDriver*)displayDriver)->init(); ////TODO Commen this in when using zybo, and add print in while
    //((DisplayDriver*)displayDriver)->clear();
    /* Initialize the queue attributes */
    struct mq_attr attr = QUEUE_ATTR_INITIALIZER;

    /* Create the message queue. The queue reader is NONBLOCK. */
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, QUEUE_PERMS, &attr);
    if(mq < 0) {
        fprintf(stderr, "[CONSUMER]: Error, cannot open the queue: %s.\n", strerror(errno));
        exit(1);
    }else{    printf("[CONSUMER]: Queue opened, queue descriptor: %d.\n", mq);}


    ssize_t bytes_read;
    char buffer[QUEUE_MSGSIZE + 1];
    while(th_consumer_running) {
        memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, QUEUE_MSGSIZE, 0);
        if(bytes_read >= 0) {
            printf("[CONSUMER]: Received message: \"%s\"\n", buffer);
        } else {//Wait for messages
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); //Double the poll speed of producer
        }
        fflush(stdout);
    }

    /* Cleanup */
    printf("[CONSUMER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

}

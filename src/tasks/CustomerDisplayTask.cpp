//
// Created by troel on 12/28/19.
//

#include "CustomerDisplayTask.hpp"

void CustomerDisplayTask::sendMessageToQ(std::string msg) {
    Queue q_send(CUSTOMER_DISPLAY_QUEUE_NAME, O_WRONLY);
    q_send.send(msg);
}

void *CustomerDisplayTask::taskHandler(CustomerDisplayTask *customerDisplay) {
    /* Create the message queue. The queue reader is NONBLOCK. */
    while(true) {
        Queue q_read(CUSTOMER_DISPLAY_QUEUE_NAME, O_RDONLY);
        std::string mes = q_read.receive();
        customerDisplay->print(1, mes);
    }
}

void CustomerDisplayTask::createQueue() {
    Queue q(CUSTOMER_DISPLAY_QUEUE_NAME, O_CREAT | O_RDWR, CD_QUEUE_MAXMSG, CD_QUEUE_MSGSIZE);
}

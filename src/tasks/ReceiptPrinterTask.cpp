//
// Created by nikolaj on 12/29/19.
//

#include <cstring>
#include <fstream>
#include "ReceiptPrinterTask.hpp"
#include "../utilities/queue.h"

void *ReceiptPrinterTask::taskHandler(ReceiptPrinterTask *receipt) {
    //displayDriver->init();
    //displayDriver->clear();
    /* Initialize the queue attributes */

    mq_unlink(QUEUE_RECEIPT);
    struct mq_attr attr = QUEUE_RECEIPT_ATTR_INITIALIZER;

    /* Create the message queue. The queue reader is NONBLOCK. */
    mqd_t mq = mq_open(QUEUE_RECEIPT, O_CREAT | O_RDONLY, QUEUE_RECEIPT_PERMS, &attr);
    if(mq < 0) {
        fprintf(stderr, "[RECEIPT CONSUMER]: Error, cannot open the queue: %s.\n", strerror(errno));
        exit(1);
    }else{    printf("[RECEIPT CONSUMER]: Queue opened, queue descriptor: %d.\n", mq);}

    ssize_t bytes_read;
    char buffer[QUEUE_RECEIPT_MSGSIZE + 1];
    while(th_consumer_running) {
        memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, QUEUE_RECEIPT_MSGSIZE, 0);
        if(bytes_read >= 0) {
            printf("[RECEIPT CONSUMER]: Received message: %s \n", buffer);

            //std::string receipt_string = receipt->stringifyReceipt();

            std::ofstream myfile;
            myfile.open("receipt.txt");
            myfile << buffer;
            myfile.close();
            std::string command_string = "lp receipt.txt";

            system(command_string.c_str());

        } else {//Wait for messages
            std::this_thread::sleep_for(std::chrono::milliseconds(5)); //Double the poll speed of producer
        }
        fflush(stdout);
    }

    /* Cleanup */
    printf("[RECEIPT CONSUMER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_RECEIPT);

}
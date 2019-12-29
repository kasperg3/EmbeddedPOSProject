//
// Created by nikolaj on 12/29/19.
//

#include <cstring>
#include <fstream>
#include "ReceiptPrinterTask.hpp"
#include "../utilities/queue.h"

void *ReceiptPrinterTask::taskHandler(ReceiptPrinterTask *receipt) {

    /* Initialize the queue attributes */
    //Queue receiptQueue(QUEUE_RECEIPT,O_RDONLY,QUEUE_RECEIPT_MAXMSG,QUEUE_RECEIPT_MSGSIZE);
    Queue receiptQueue(QUEUE_RECEIPT, O_RDONLY);
    std::string buffer;
    buffer.clear();

    while (th_consumer_running){
        buffer = receiptQueue.receive();
        if(!buffer.empty()){
            std::cout << "RPT message received" << std::endl;
           std::ofstream myfile;
           myfile.open("receipt.txt");
           myfile << buffer;
           myfile.close();
           std::string command_string = "lp receipt.txt";
           system(command_string.c_str());
           buffer.clear();
        }
    }
}
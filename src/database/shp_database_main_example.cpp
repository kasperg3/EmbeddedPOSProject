#include <iostream>
#include "db_interface.hpp"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

using namespace std;

const char* barcode_scanner_queue_name = "/barcode_scanner_queue";
const char* card_reader_queue_name = "/card_reader_queue";
const char* customer_display_queue_name = "/customer_display_queue";
const char* receipt_printer_queue_name = "/receipt_printer_queue";
const int MAXMSG = 10;
const int MSGSIZE = 8192;

string state = "scan";

int main(int argc, char** argv)
{
    struct mq_attr queue_attributes;
    queue_attributes.mq_maxmsg = MAXMSG;
    queue_attributes.mq_msgsize = MSGSIZE;
    mode_t mode = 0666;

    mqd_t barcode_scanner_queue = mq_open(barcode_scanner_queue_name, O_CREAT | O_RDONLY | O_NONBLOCK, mode, &queue_attributes);
    mqd_t card_reader_queue = mq_open(card_reader_queue_name, O_CREAT | O_RDONLY | O_NONBLOCK, mode, &queue_attributes);
    mqd_t customer_display_queue = mq_open(customer_display_queue_name, O_CREAT | O_WRONLY, mode, &queue_attributes);
    mqd_t receipt_printer_queue = mq_open(receipt_printer_queue_name, O_CREAT | O_WRONLY, mode, &queue_attributes);

    if(barcode_scanner_queue == (mqd_t) -1)
        cout << "Could not open barcode scanner queue: " << strerror(errno) << endl;
    if(card_reader_queue == (mqd_t) -1)
        cout << "Could not open card reader queue: " << strerror(errno) << endl;
    if(customer_display_queue == (mqd_t) -1)
        cout << "Could not open customer display queue: " << strerror(errno) << endl;
    if(receipt_printer_queue == (mqd_t) -1)
        cout << "Could not open receipt printer queue: " << strerror(errno) << endl;



//    DatabaseInterface dbi;

    //Super loop:
//    while(true)
//    {
//        Receipt receipt = dbi.createNewReceipt();
//        string barcode;
//        if(state == "scan")
//        {
//            if(mq_receive(barcode_scanner_queue, (char*) barcode.c_str(), MSGSIZE, NULL) < 0)
//                cout << "Failed to receive a barcode: " << strerror(errno) << endl;
//            else
//            {
//                cout << "Received the following barcode: " << barcode << endl;
//                SimpleItem item = dbi.getSimpleItemByBarcode(barcode);
//                receipt.addReceiptLine(item.getId(), item.getName(), item.getUnitPrice(), 1); //Add 1 and use stock price
//            }

//        }
//        else if(state == "pay")
//        {
//            //Do stuff
//        }

//    }



    //Test completeTransaction():
//    Receipt receipt = dbi.createNewReceipt();
//    SimpleItem snickers = dbi.getSimpleItemById(112);
//    SimpleItem pepsi = dbi.getSimpleItemByName("Pepsi");
//    receipt.addReceiptLine(snickers.getId(), snickers.getName(), snickers.getUnitPrice(), 2); //Add two snickers to receipt
//    receipt.addReceiptLine(pepsi.getId(), pepsi.getName(), pepsi.getUnitPrice(), 2); //Add two pepsis

//    receipt.setPaymentStatus("payed"); //When should you actually do this?
//    dbi.completeTransaction(receipt);






    return 0;
}

/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>

#include "src/Core.h"
#include "src/utilities/queue.h"
#include "src/database/db_interface.hpp"
#include "src/state_machine_constants.h"
using namespace std;



#define SCAN_INIT "scan_init"
#define SCAN "scan"
#define KEYBOARD_HANDLER "keyboard_handler"


Queue* barcode_queue;
Queue* keyboard_queue;
Queue* card_queue;
Queue* customer_display_queue;
Queue* receipt_queue;

string state = "scan_init";



void init();


int main()
{
    init();

    //Super loop:
//    while(true)
//    {

//    }

    return 0;
}


void scan_sm()
{

    if(state == "scan_init")
    {

    }
}


void init()
{
    barcode_queue = Queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE);
    keyboard_queue = Queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK, QUEUE_KEYBOARD_MAXMSG, QUEUE_KEYBOARD_MSGSIZE);
    card_queue = Queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK, QUEUE_CARDREADER_MAXMSG, QUEUE_CARDREADER_MSGSIZE);
    customer_display_queue = Queue(CUSTOMER_DISPLAY_QUEUE_NAME, O_WRONLY, CD_QUEUE_MAXMSG, CD_QUEUE_MSGSIZE);
    receipt_queue = Queue(QUEUE_RECEIPT, O_WRONLY, QUEUE_RECEIPT_MAXMSG, QUEUE_RECEIPT_MSGSIZE);
}

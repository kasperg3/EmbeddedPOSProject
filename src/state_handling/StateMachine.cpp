//
// Created by kasper on 12/29/19.
//

#include <zconf.h>
#include "StateMachine.h"

StateMachine::StateMachine() {
}


void StateMachine::init(void) {
    barcodeQueue = Queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE);
    keyboardQueue = Queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK, QUEUE_KEYBOARD_MAXMSG, QUEUE_KEYBOARD_MSGSIZE);
    cardQueue = Queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK, QUEUE_CARDREADER_MAXMSG, QUEUE_CARDREADER_MSGSIZE);
    customerDisplayQueue = Queue(CUSTOMER_DISPLAY_QUEUE_NAME, O_WRONLY, CD_QUEUE_MAXMSG, CD_QUEUE_MSGSIZE);
    receiptQueue = Queue(QUEUE_RECEIPT, O_WRONLY, QUEUE_RECEIPT_MAXMSG, QUEUE_RECEIPT_MSGSIZE);



}

void StateMachine::start() {
    while(true)
    {
        checkInputs();
        updateState();

        if(state == EXIT)
            return;

        usleep(UPDATE_PERIOD);
    }
}

void StateMachine::checkInputs() {
    barcodeInput = barcodeQueue.receive();
    keyboardInput = keyboardQueue.receive();
    cardInput = cardQueue.receive();
    customerDisplayInput = customerDisplayQueue.receive();
    receiptInput = receiptQueue.receive();
}

void StateMachine::updateState() {


}

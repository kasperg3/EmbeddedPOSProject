#include "shpstatemachine.h"

#include <iostream>
#include <unistd.h>
using namespace std;

#define ms_sleep(ms) usleep(ms * 1000)

ShpStateMachine::ShpStateMachine()
    : barcode_queue(Queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK)),
      keyboard_queue(Queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK)),
      card_reader_queue(Queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK)),
      receipt_queue(Queue(QUEUE_RECEIPT, O_WRONLY | O_NONBLOCK)),
      context(zmq::context_t(1)), customer_display_socket(zmq::socket_t(context, ZMQ_REQ))
{
    customer_display_socket.connect("tcp://" + PC_IP + ":" + CUSTOMER_DISPLAY_PORT);
}

void ShpStateMachine::run()
{
    state = STATE_SCAN;
    receipt = dbi.createNewReceipt();

    const char* message = "Hello from shpmfewfewfewachine";
    customer_display_socket.send(message, strlen(message));

//    while(true)
//    {
//        cout << "Current state: " << state << endl;
//        register_events_and_values();
//        fsm();
//        ms_sleep(500);
//    }
}

void ShpStateMachine::register_events_and_values()
{
    if(!barcode_queue.empty())
    {
        barcode = barcode_queue.receive();
        event_queue.push(EVENT_BARCODE_SCANNED);
    }
    if(!keyboard_queue.empty())
    {
        key = keyboard_queue.receive();
        event_queue.push(EVENT_KEYBOARD_PRESSED);
    }
    if(!card_reader_queue.empty())
    {
        card_number = card_reader_queue.receive();
        event_queue.push(EVENT_CARD_READ);
    }

    update_event();
}

void ShpStateMachine::update_event()
{
    if(!event_queue.empty())
    {
        event = event_queue.front();
        event_queue.pop();
    }
    else
        event = NO_EVENT;
}

void ShpStateMachine::fsm()
{
    scan_fsm();
    pay_fsm();
}


void ShpStateMachine::scan_fsm()
{
    switch(state)
    {
    case STATE_SCAN:
        switch(event)
        {
        case EVENT_BARCODE_SCANNED:
        {
            SimpleItem item = dbi.getSimpleItemByBarcode(barcode);
            receipt.addReceiptLine(item.getId(), item.getName(),item.getUnitPrice(), 1);
            break;
        }

        case EVENT_KEYBOARD_PRESSED:
            if(key == "ESC")
                receipt = dbi.createNewReceipt();
            else if(key == "<ENTER>")
                state = STATE_PAY;
            else if(key_is_a_number())
            {
                state = STATE_MULTIPLY_GOODS;
                multiplier = key;
            }
            break;
        }
        break;


    case STATE_MULTIPLY_GOODS:
        switch(event)
        {
        case EVENT_BARCODE_SCANNED:
        {
            SimpleItem item = dbi.getSimpleItemByBarcode(barcode);
            receipt.addReceiptLine(item.getId(), item.getName(), item.getUnitPrice(), stoi(multiplier));
            state = STATE_SCAN;
            break;
        }
        case EVENT_KEYBOARD_PRESSED:
            if(key == "ESC")
            {
                receipt = dbi.createNewReceipt();
                state = STATE_SCAN;
            }
            else if(key == "<ENTER>")
                state = STATE_PAY;
            else if(key_is_a_number())
                multiplier += key;
            break;
        }
        break;
    }

}

bool ShpStateMachine::key_is_a_number()
{
    return key == "0" || key == "1" || key == "2" || key == "3" || key == "4" ||
           key == "5" || key == "6" || key == "7" || key == "8" || key == "9";
}


void ShpStateMachine::pay_fsm()
{
    switch(state)
    {
    case STATE_PAY:
        cout << "Made it to STATE_PAY" << endl;
        cout << receipt.getReceiptLines()[0].name << endl;
        cout << receipt.getReceiptLines()[0].quantity << endl;

        //cout << receipt.stringifyReceipt() << endl;
        break;
    }
}











#include "shpstatemachine.h"

#include <iostream>
#include <unistd.h>
using namespace std;

#define ms_sleep(ms) usleep(ms * 1000)

ShpStateMachine::ShpStateMachine()
    : barcode_queue(Queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK)),
      keyboard_queue(Queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK)),
      card_reader_queue(Queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK)),
      numpad_queue(Queue(QUEUE_NUMPAD, O_RDONLY | O_NONBLOCK)),

      receipt_queue(Queue(QUEUE_RECEIPT, O_WRONLY | O_NONBLOCK)),
      lcd_queue(Queue(QUEUE_LCD, O_WRONLY | O_NONBLOCK)),

      context(zmq::context_t(1)), customer_display_socket(zmq::socket_t(context, ZMQ_REQ))
{
    customer_display_socket.connect("tcp://" + PC_IP + ":" + CUSTOMER_DISPLAY_PORT);
}

void ShpStateMachine::run()
{
    state = STATE_SCAN;
    receipt = dbi.createNewReceipt();
    //print_on_customer_display("Den tredje januar\n");

    while(true)
    {
        cout << "Current state: " << state << endl;
        register_events_and_values();
        fsm();
        ms_sleep(500);
    }
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
        keyboard_key = keyboard_queue.receive();
        event_queue.push(EVENT_KEYBOARD_PRESSED);
    }
    if(!card_reader_queue.empty())
    {
        card_number = card_reader_queue.receive();
        event_queue.push(EVENT_CARD_READ);
    }
    if(!numpad_queue.empty())
    {
        numpad_key = numpad_queue.receive();
        event_queue.push(EVENT_NUMPAD_PRESSED);
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
            if(keyboard_key == "ESC")
                receipt = dbi.createNewReceipt();
            else if(keyboard_key == "<ENTER>")
                state = STATE_PAY;
            else if(keyboard_key_is_a_number())
            {
                state = STATE_MULTIPLY_GOODS;
                multiplier = keyboard_key;
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
            if(keyboard_key == "ESC")
            {
                receipt = dbi.createNewReceipt();
                state = STATE_SCAN;
            }
            else if(keyboard_key == "<ENTER>")
                state = STATE_PAY;
            else if(keyboard_key_is_a_number())
                multiplier += keyboard_key;
            break;
        }
        break;
    }

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


bool ShpStateMachine::keyboard_key_is_a_number()
{
    return keyboard_key == "0" || keyboard_key == "1" || keyboard_key == "2" || keyboard_key == "3" || keyboard_key == "4" ||
            keyboard_key == "5" || keyboard_key == "6" || keyboard_key == "7" || keyboard_key == "8" || keyboard_key == "9";
}


void ShpStateMachine::print_on_customer_display(string request)
{
    customer_display_socket.send(request.data(), request.size());
    zmq::message_t reply;
    customer_display_socket.recv(&reply);
}











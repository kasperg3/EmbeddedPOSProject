#include "shpstatemachine.h"
#include "../peripherals/CardReader.hpp"

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
    setup_state_map();

}

void ShpStateMachine::run()
{
    state = STATE_SCAN_INIT;
    while(true)
    {
        //cout << "Current state: " << state_map[state] << endl;
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
//        cout << "Received a numpad_queue event" << endl;
//        cout << "numpad_key: " << numpad_key << endl;
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
    case STATE_SCAN_INIT:
        lcd_queue.send("2");
        lcd_queue.send("0Welcome to ESD");
        print_on_customer_display("Welcome to ESD Shop <3");

        cout << "Requesting new receipt ID from database" << endl;
        receipt = dbi.createNewReceipt();
        change_state_to(STATE_SCAN);
        break;

    case STATE_SCAN:
        switch(event)
        {
        case EVENT_BARCODE_SCANNED:
        {
            SimpleItem item = dbi.getSimpleItemByBarcode(barcode);
            receipt.addReceiptLine(item.getId(), item.getName(),item.getUnitPrice(), 1);
            string stringified_line = receipt.stringifyLineToDisplay(receipt.getReceiptLines()[receipt.getReceiptLines().size()-1]);
            print_on_customer_display(stringified_line);
            cout <<  stringified_line << endl;
            break;
        }
        case EVENT_KEYBOARD_PRESSED:
            if(keyboard_key == "<ESC>")
                change_state_to(STATE_SCAN_INIT);
            else if(keyboard_key == "<Enter>")
                change_state_to(CHOOSE_PAYMENT);
            else if(keyboard_key_is_a_number())
            {
                change_state_to(STATE_MULTIPLY_GOODS);
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
            print_on_customer_display(receipt.stringifyLineToDisplay(receipt.getReceiptLines()[receipt.getReceiptLines().size()-1]));
            change_state_to(STATE_SCAN);
            break;
        }
        case EVENT_KEYBOARD_PRESSED:
            if(keyboard_key == "<ESC>")
                change_state_to(STATE_SCAN_INIT);

            else if(keyboard_key == "<Enter>")
                change_state_to(CHOOSE_PAYMENT);
            else if(keyboard_key_is_a_number()) {
                multiplier += keyboard_key;
            }
            break;
        }
        break;
    }

}



void ShpStateMachine::pay_fsm()
{
    switch(state)
    {
    case CHOOSE_PAYMENT:
        if(event == EVENT_KEYBOARD_PRESSED) {
            if (keyboard_key == "1") {
                change_state_to(BY_CARD);
                lcd_queue.send("2");
                lcd_queue.send("0Swipe card");
            }
            else if (keyboard_key == "2")
                change_state_to(BY_CASH);
            else if (keyboard_key == "<ESC>")
                change_state_to(STATE_SCAN_INIT);
        }
        break;

    case BY_CARD:
        if(event == EVENT_CARD_READ)
            change_state_to(VALIDATE_CARD);
        else if(event == EVENT_KEYBOARD_PRESSED)
            if (keyboard_key == "<ESC>")
                change_state_to(CHOOSE_PAYMENT);
        break;

    case BY_CASH:
        if(event == EVENT_KEYBOARD_PRESSED) {
            if (keyboard_key == "<ESC>")
                change_state_to(CHOOSE_PAYMENT);
            if (keyboard_key == "<Enter>") {
                change_state_to(CHOOSE_PRINT);
                receipt.setPaymentStatus("payed");
                dbi.completeTransaction(receipt);
            }
        }

        break;

    case VALIDATE_CARD:
        //Luhns algo to validate card...
        pin.clear();
        change_state_to(ENTER_PIN);
        //if invalid
        //state = BY_CARD;
        lcd_queue.send("2");
        lcd_queue.send("0Enter Pin:");
        lcd_queue.send("1Pin: ");
    break;

    case ENTER_PIN:
        if(event == EVENT_NUMPAD_PRESSED){
            pin += numpad_key;
            std::string displayString = "1Pin:";
            for(size_t i = 0; i < pin.size(); i++){
                displayString.append("*");
            }
            lcd_queue.send(displayString);
        }
        if(pin.size() > 3)
            change_state_to(VALIDATE_PIN);
        if(event == EVENT_KEYBOARD_PRESSED)
            if (keyboard_key == "<ESC>")
                change_state_to(CHOOSE_PAYMENT);
        break;
    case VALIDATE_PIN:
        if(pin == "1234"){
            //end transaction
            lcd_queue.send("2");
            lcd_queue.send("0Purchase");
            lcd_queue.send("1successful");
            receipt.setPaymentStatus("payed");
            dbi.completeTransaction(receipt);
            change_state_to(CHOOSE_PRINT);
        }
        else
        {
            lcd_queue.send("2");
            lcd_queue.send("0Wrong pin");
            lcd_queue.send("1Pin:");
            pin.clear();
            change_state_to(ENTER_PIN);
        }
        break;

    case CHOOSE_PRINT:
        if(event == EVENT_KEYBOARD_PRESSED){
            if(keyboard_key == "<Enter>"){
                //stringify receipt and put in queue
                receipt_queue.send(receipt.stringifyReceipt());
                change_state_to(STATE_SCAN_INIT);
            }
            if(keyboard_key == "<ESC>")
                change_state_to(STATE_SCAN_INIT);
        }
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


//enum {STATE_SCAN_INIT, STATE_SCAN, STATE_MULTIPLY_GOODS,
//    CHOOSE_PAYMENT, BY_CARD, BY_CASH, VALIDATE_CARD, ENTER_PIN, VALIDATE_PIN, CHOOSE_PRINT};

void ShpStateMachine::setup_state_map()
{
    state_map[STATE_SCAN_INIT] = "STATE_SCAN_INIT";
    state_map[STATE_SCAN] = "STATE_SCAN";
    state_map[STATE_MULTIPLY_GOODS] = "STATE_MULTIPLY_GOODS";
    state_map[CHOOSE_PAYMENT] = "CHOOSE_PAYMENT";
    state_map[BY_CARD] = "BY_CARD";
    state_map[BY_CASH] = "BY_CASH";
    state_map[VALIDATE_CARD] = "VALIDATE_CARD";
    state_map[ENTER_PIN] = "ENTER_PIN";
    state_map[VALIDATE_PIN] = "VALIDATE_PIN";
    state_map[CHOOSE_PRINT] = "CHOOSE_PRINT";
}

void ShpStateMachine::change_state_to(int new_state) {
    state = new_state;
    cout << "Current state is: " << state_map[state] << endl;
}










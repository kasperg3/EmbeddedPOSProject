#ifndef SHPSTATEMACHINE_H
#define SHPSTATEMACHINE_H

#include "queue.h"
#include "db_interface.hpp"
#include "statemachine_constants.h"
#include <queue>
#include <string>


class ShpStateMachine
{
public:
    ShpStateMachine();
    void run();


private:
    Receipt receipt;
    DatabaseInterface dbi;

    Queue barcode_queue;
    Queue card_reader_queue;
    Queue keyboard_queue;
    Queue receipt_queue;
    Queue numpad_queue;
    Queue lcd_queue;

    zmq::context_t context;
    zmq::socket_t customer_display_socket;

    std::string barcode;
    std::string card_number;
    std::string keyboard_key;
    std::string numpad_key;

    std::string multiplier;

    std::queue<int> event_queue;
    int event;
    int state;

private:
    void register_events_and_values();
    void update_event();

    void fsm();
    void scan_fsm();
    void pay_fsm();

    bool keyboard_key_is_a_number();
    void print_on_customer_display(std::string request);


};

#endif // SHPSTATEMACHINE_H

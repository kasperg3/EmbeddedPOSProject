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
    Queue customer_display_queue;
    Queue receipt_queue;

    std::string barcode;
    std::string card_number;
    std::string key;

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

    bool key_is_a_number();


};

#endif // SHPSTATEMACHINE_H

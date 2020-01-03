#ifndef SHPSTATEMACHINE_H
#define SHPSTATEMACHINE_H

#include "../Core.h"
#include "../database/receipt.hpp"
#include "../database/db_interface.hpp"
#include "../utilities/queue.h"
#include <queue>
#include <string>
#include <map>

enum {NO_EVENT, EVENT_BARCODE_SCANNED, EVENT_KEYBOARD_PRESSED, EVENT_CARD_READ, EVENT_NUMPAD_PRESSED};
enum {STATE_SCAN_INIT, STATE_SCAN, STATE_MULTIPLY_GOODS,
    CHOOSE_PAYMENT, BY_CARD, BY_CASH, VALIDATE_CARD, ENTER_PIN, VALIDATE_PIN, CHOOSE_PRINT};




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
    std::string numpad_key = "";
    std::string pin = "";
    std::string multiplier;

    std::queue<int> event_queue;
    int event;
    int state;

    std::map<int, std::string> state_map;


private:
    void register_events_and_values();
    void update_event();

    void fsm();
    void scan_fsm();
    void pay_fsm();

    bool keyboard_key_is_a_number();
    void print_on_customer_display(std::string request);

    void setup_state_map();


};

#endif // SHPSTATEMACHINE_H

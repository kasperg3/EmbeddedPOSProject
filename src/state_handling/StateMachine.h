//
// Created by kasper on 12/29/19.
//

#ifndef EMBEDDEDPROJ_STATEMACHINE_H
#define EMBEDDEDPROJ_STATEMACHINE_H

#include "../utilities/queue.h"
#include "../Core.h"
#include "../utilities/queue.h"

#define UPDATE_PERIOD 10000 // [μs]

class StateMachine {
public:
    StateMachine();
    void init();
    void start();
    void checkInputs();
    void updateState();


private:

    Queue barcodeQueue;
    Queue keyboardQueue;
    Queue cardQueue;
    Queue customerDisplayQueue;
    Queue receiptQueue;

    enum State {
        EXIT,
        INIT,
        SCAN,
        SCAN_INIT,
        SCAN_KEYBOARD_HANDLER,
        PAY,
        PAY_KEYBOARD_HANDLER,
        VALIDATE,
        PRINT,
        PRINT_KEYBOARD_HANDLER
    };

    State state;

    //Inputs
    std::string barcodeInput;
    std::string keyboardInput;
    std::string cardInput;
    std::string customerDisplayInput;
    std::string receiptInput;
};


#endif //EMBEDDEDPROJ_STATEMACHINE_H

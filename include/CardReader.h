//
// Created by kasper on 9/19/19.
//

#ifndef EMBEDDEDPROJ_CARDREADER_H
#define EMBEDDEDPROJ_CARDREADER_H

#include <iostream>
#include <iomanip>
#include <fstream>
enum States {
    ST_IDLE,
    ST_FAILURE,
    ST_WAITFORSWIPE,
    ST_APPROVEAMOUNT,
    ST_INPUTPIN,
    ST_STOP
};

class CardReader {


public:
    CardReader();
    ~CardReader();
    int runCardReader();
    int waitForSwipe();
    bool luhnAlgorithm();
    States currentState = ST_IDLE;

private:
    std::string cardNumber;
};

#endif //EMBEDDEDPROJ_CARDREADER_H

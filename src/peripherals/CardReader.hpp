//
// Created by kasper on 9/19/19.
//

#ifndef EMBEDDEDPROJ_CARDREADER_HPP
#define EMBEDDEDPROJ_CARDREADER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>

class CardReader {
    enum States {
        ST_IDLE,
        ST_FAILURE,
        ST_WAITFORSWIPE,
        ST_APPROVEAMOUNT,
        ST_INPUTPIN,
        ST_STOP
    };


public:
    CardReader();
    ~CardReader();
    int runCardReader();
    int waitForSwipe();
    bool luhnAlgorithm();
    States currentState;

private:
    std::string cardNumber;
};

#endif //EMBEDDEDPROJ_CARDREADER_HPP

//
// Created by kasper on 9/19/19.
//

#ifndef EMBEDDEDPROJ_CARDREADER_H
#define EMBEDDEDPROJ_CARDREADER_H

#include <iostream>
#include <iomanip>
#include <fstream>

class CardReader {

public:
    CardReader();
    int waitForSwipe();
    bool luhnAlgorithm();
    std::string getCardNumber();
    void setCardNumber(std::string);


private:
    std::string cardNumber;
};


#endif //EMBEDDEDPROJ_CARDREADER_H

//
// Created by kasper on 10/4/19.
//

#ifndef EMBEDDEDPROJ_NUMPADDRIVER_HPP
#define EMBEDDEDPROJ_NUMPADDRIVER_HPP


#include <vector>
#include "GPIO.hpp"
#include <array>
#include <iostream>
class NumpadDriver {
private:
    GPIO column[4];
    GPIO row[4];
    int getValue();
public:
    NumpadDriver();
    ~NumpadDriver();
    void init();
    int check();
};


#endif //EMBEDDEDPROJ_NUMPADDRIVER_HPP

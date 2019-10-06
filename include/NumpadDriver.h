//
// Created by kasper on 10/4/19.
//

#ifndef EMBEDDEDPROJ_NUMPADDRIVER_H
#define EMBEDDEDPROJ_NUMPADDRIVER_H


#include <vector>
#include "../include/GPIO.h"
class NumpadDriver {
private:
    std::vector<GPIO> collumn;
    std::vector<GPIO> row;

public:
    NumpadDriver();
    ~NumpadDriver();
    void init();
    int check();
    int getValue();
};


#endif //EMBEDDEDPROJ_NUMPADDRIVER_H

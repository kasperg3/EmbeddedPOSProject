//
// Created by kasper on 10/4/19.
//

#include <sstream>
#include "NumpadDriver.hpp"

NumpadDriver::NumpadDriver() {

}

NumpadDriver::~NumpadDriver() {
    //Unexport the pins
    for(int i = 0; i < 4; i++){
        column[i].unexportPin();
        row[i].unexportPin();
    }
}

void NumpadDriver::init() {
    column[0] = GPIO("995");
    column[1] = GPIO("994");
    column[2] = GPIO("993");
    column[3] = GPIO("992");
    row[0] = GPIO("999");
    row[1] = GPIO("998");
    row[2] = GPIO("997");
    row[3] = GPIO("996");

    for(int i = 0; i < 4; i++){
        column[i].exportPin();
        column[i].setPinDirection("out");
        row[i].exportPin();
        row[i].setPinDirection("in");
    }
}

int NumpadDriver::check() {
    return getValue();
}

int NumpadDriver::getValue() {
    int rowIndex = 0;
    int colIndex = 0;

    int numpadMap[4][4] = {{1,2,3,10},{4,5,6,11},{7,8,9,12},{0,15,14,13}};

    for(int i = 0; i < 4; i++){
        std::string pinValue;
        column[i].setPinValue("0");
        for(int j = 0; j < 4; j++){
            row[j].getPinValue(pinValue);
            if(pinValue == "0"){
                colIndex = i+1;
                rowIndex = j+1;
            }
        }
        column[i].setPinValue("1");
    }
    if(rowIndex == 0 and colIndex == 0)
        return -1;

    return numpadMap[rowIndex-1][colIndex-1];
}

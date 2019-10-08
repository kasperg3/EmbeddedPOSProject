//
// Created by kasper on 10/4/19.
//

#ifndef EMBEDDEDPROJ_DISPLAYDRIVER_H
#define EMBEDDEDPROJ_DISPLAYDRIVER_H

#include "GPIO.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <chrono>
#include <thread>

class DisplayDriver {
private:
    GPIO data_bit[8];
    GPIO register_select;
    GPIO read_write;
    GPIO enable;
    GPIO backlight;

    void initGPIO();
    void initDisplay();
    void setDataBits(std::string);
    void setDataBits(std::bitset<8>);
    void pulseEnableSignal();
    void sendCommand(std::string);
    void sendData(std::string);
    void sendData(char);
    void setAddress(int);
public:
    DisplayDriver();
    ~DisplayDriver();
    void init();
    void print(int, char);
    void print(std::string);
    void clear();
};


#endif //EMBEDDEDPROJ_DISPLAYDRIVER_H

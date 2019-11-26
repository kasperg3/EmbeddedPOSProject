/*
 * DisplayDriver.h
 *
 *  Created on: Oct 8, 2019
 *      Author: nikolaj
 */

#ifndef DISPLAYDRIVER_H_
#define DISPLAYDRIVER_H_

#include "GPIO.hpp"

class DisplayDriver {
public:
	DisplayDriver();
    int init();
    int print(int, std::string);
    int clear();

	~DisplayDriver();
private:
    int initGPIOs();
    int initDisplay();
    int setDataBits(std::string databits);
    int pulseEnableSignal();
    int sendCommand(std::string command);
    int sendData(std::string data);

    GPIO data_bit[8];
    GPIO register_select;
    GPIO read_write;
    GPIO enable;

};

#endif /* DISPLAYDRIVER_H_ */

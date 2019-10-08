//
// Created by kasper on 10/4/19.
//
#include <bits/stdc++.h>
#include "../include/DisplayDriver.h"

DisplayDriver::DisplayDriver() {
    //Databit setup
    data_bit[7] = GPIO("1016");
    data_bit[6] = GPIO("1017");
    data_bit[5] = GPIO("1018");
    data_bit[4] = GPIO("1019");
    data_bit[3] = GPIO("1020");
    data_bit[2] = GPIO("1021");
    data_bit[1] = GPIO("1022");
    data_bit[0] = GPIO("1023");

    //RS Setup
    register_select = GPIO("1012");
    //Read/Write signal: High for Read mode, Low for Write mode, RW
    read_write = GPIO("1013");
    //Read/Write Enable: High for Read, falling edge writes data, E
    enable = GPIO("1014");
    //Optional back-light enable (not connected on the Pmod CLP
    backlight = GPIO("1015");
}

DisplayDriver::~DisplayDriver() {

}

void DisplayDriver::init() {
    std::cout << "[INFO] initialising GPIO" << std::endl;
    initGPIO();
    std::cout << "[INFO] initialising Display" << std::endl;
    initDisplay();
}

void DisplayDriver::print(int address, char character) {
    sendData(character);
    sendCommand("0000000110");//Shift Cursor and address increment
}


/*
 * Clear display by writing a 20H to all DDRAM locations;
 * set DDRAM address register to 00H;
 * and return cursor to home.
 */
void DisplayDriver::clear() {
    sendCommand("0000000001");      //Clear display
    for(int i = 0; i < 127; i++){
        sendCommand(std::string("001").append(std::bitset<7>(i).to_string()));//Sets address
        sendCommand("1000100000");  //Sets address value
    }
    sendCommand("0010000000");//Sets to address 0
    sendCommand("0000000011");//Return cursor home
}

void DisplayDriver::initGPIO() {
    for(auto & gpio : data_bit){
        gpio.exportPin();
        gpio.setPinDirection("out");
        gpio.clear();
    }
    register_select.exportPin();
    register_select.setPinDirection("out");

    read_write.exportPin();
    read_write.setPinDirection("out");

    enable.exportPin();
    enable.setPinDirection("out");
    enable.set();

    backlight.exportPin();
    backlight.setPinDirection("out");
}

void DisplayDriver::initDisplay() {
    //Startup Sequence
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    register_select.clear();
    read_write.clear();
    sendCommand("0000111000");
    std::this_thread::sleep_for(std::chrono::microseconds(37));
    sendCommand("0000001110");
    std::this_thread::sleep_for(std::chrono::microseconds(37));
    sendCommand("0000000001");
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    sendCommand("0000000111");

    //Enable backlight
    backlight.set();
    pulseEnableSignal();
}

void DisplayDriver::setDataBits(std::string bitString) {
    for(int i = 0; i < bitString.length(); i++){
        if(bitString[i] == '1')
            data_bit[i].set();
        else
            data_bit[i].clear();
    }
}

void DisplayDriver::setDataBits(std::bitset<8> binarySet) {
    setDataBits(binarySet.to_string());
}

void DisplayDriver::pulseEnableSignal() {
    enable.clear();
    enable.set();
}

/*
 * Bit string has to be 10 bits long
 */
void DisplayDriver::sendCommand(std::string bitString) {
    char subArray[8];
    for(int i = 2; i < bitString.length(); i++){
        subArray[i-2] = bitString[i];
    }
    setDataBits(subArray);

    register_select.setPinValue(std::string(1,bitString[0]));
    read_write.setPinValue(std::string(1,bitString[1]));
    pulseEnableSignal();
}

/*
 * Sends a sequence of data to the RAM
 */
void DisplayDriver::sendData(std::string bitString) {}

/*
 * Writes data to the RAM
 */
void DisplayDriver::sendData(char character) {
    sendCommand(std::string("10").append(std::bitset<8>(character).to_string()));
}

void DisplayDriver::setAddress(int addr) {
    sendCommand(std::string("001").append(std::bitset<7>(addr).to_string()));
}

void DisplayDriver::print(std::string printString) {
    clear();

    for(int i = 0; i < printString.length(); i++){
        print(i+1,printString[i]);
    }
}

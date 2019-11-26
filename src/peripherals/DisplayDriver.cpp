/*
 * DisplayDriver.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: nikolaj
 */

#include "DisplayDriver.hpp"
#include <chrono>
#include <thread>
#include <bitset>

DisplayDriver::DisplayDriver() {
    register_select = GPIO(1012);
    read_write = GPIO(1013);
    enable = GPIO(1014);

    data_bit[7] = GPIO(1016);
    data_bit[6] = GPIO(1017);
    data_bit[5] = GPIO(1018);
    data_bit[4] = GPIO(1019);
    data_bit[3] = GPIO(1020);
    data_bit[2] = GPIO(1021);
    data_bit[1] = GPIO(1022);
    data_bit[0] = GPIO(1023);

}


DisplayDriver::~DisplayDriver() {
    for (int i = 0; i < 12; ++i) {
        data_bit[i].unexportPin();
    }
    register_select.unexportPin();
    read_write.unexportPin();
    enable.unexportPin();
}


int DisplayDriver::initGPIOs() {
    for (int i = 0; i < 8; ++i) {
        data_bit[i].exportPin();
        data_bit[i].setPinDirection("out");;
    }
    register_select.exportPin();
    register_select.setPinDirection("out"); //High for data transfer low for instruction transfer

    read_write.exportPin(); //high for read mode, low for write mode
    read_write.setPinDirection("out");

    enable.exportPin();             //read/write enable
    enable.setPinDirection("out");  //High for read, falling edge writes data
    return 0;
}


int DisplayDriver::initDisplay() {

    std::chrono::milliseconds mil(1);
    std::this_thread::sleep_for(mil*23);    //set function
    sendCommand("Function");

    std::this_thread::sleep_for(mil*1);       //display set
    sendCommand("Display");

    std::this_thread::sleep_for(mil*1);       //display clear
    sendCommand("Clear");

    std::this_thread::sleep_for(mil*5);
    sendCommand("Entry Mode");

    return 0;
}


int DisplayDriver::init() {
    initGPIOs();
    initDisplay();
    return 0;
}


int DisplayDriver::print(int address, std::string data) {
    std::bitset<7> foo (address);
    std::string temp = "001" + foo.to_string();
    setDataBits(temp);               //sets the address
    pulseEnableSignal();
    sendData(data);                  //sends
    return 0;
}


int DisplayDriver::clear(){
    sendCommand("Clear");
    return 0;
}


int DisplayDriver::pulseEnableSignal() {
    enable.setPinValue("1");
    enable.setPinValue("0");
    return 0;
}


int DisplayDriver::sendData(std::string data) {     //send a string to display
    for (int i = 0; i < data.length(); ++i) {
        std::bitset<8> foo (data.at(i));
        setDataBits("10"+ foo.to_string());
        pulseEnableSignal();
    }
    return 0;
}


int DisplayDriver::setDataBits(std::string databits) {  //send to display or to write stuff or to use commands one Char at a time
    if(databits.length() != 10) {
        std::cout << "invalid length of databits" << std::endl;
        return 0;
    }

    std::string register_string(1,databits[0]);
    std::string read_write_string(1,databits[1]);

    register_select.setPinValue(register_string);
    read_write.setPinValue(read_write_string);

    for (int i = 0; i < 8; ++i) {
        std::string s(1,databits[i+2]);
        data_bit[i].setPinValue(s);
    }
    return 0;
}


int DisplayDriver::sendCommand(std::string command) {  //check reference-manual Pmod CLP instruction codes
    std::cout << "command: " << command << std::endl;
    if(command == "Clear"){ //0000 0000 01
        setDataBits("0000000001");
    }

    else if(command == "Home"){ //0000 0000 1x
        setDataBits("0000000010");
    }

    else if(command == "Display"){  //0000 0011 11
        setDataBits("0000001111");
    }

    else if(command == "Function"){//0000 1110 xx
        setDataBits("0000111000");
    }

    else if(command == "Entry Mode"){  //0000 0001 11
        setDataBits("0000000110");
    }

    else{
        std::cout << "invalid command: " << command << std::endl;
        return -1;
    }
    pulseEnableSignal();
    return 0;
}
//
// Created by troel on 12/28/19.
//

#ifndef EMBEDDEDPROJ_CUSTOMERDISPLAY_HPP
#define EMBEDDEDPROJ_CUSTOMERDISPLAY_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>

class CustomerDisplay {
public:
    CustomerDisplay();
    int print(int, std::string);
    void init();
    int readDisplay();

    ~CustomerDisplay();
private:
    int sendCommand(std::string command);
    int writeToFile(std::string);
    int readFromFile(std::string&);

    std::string path = "/dev/ttyUSB0";
//    std::string path = "/dev/display";
    std::string clear = "\x0C";
    std::string clear_line = "\x18";
    std::string move_l1 = "\x1F\x24\01\x01";
    std::string move_l2 = "\x1F\x24\x01\x02";
    std::string set_com_mode = "\x02\x05\x43\x31\x03";
    std::string init_display = "\x1B\x40";


};


#endif //EMBEDDEDPROJ_CUSTOMERDISPLAY_HPP

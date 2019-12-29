//
// Created by troel on 12/28/19.
//

#include "CustomerDisplay.hpp"


CustomerDisplay::CustomerDisplay() {
}

int CustomerDisplay::print(int line, std::string msg) {
    if (line == 1){
        writeToFile(clear);
        writeToFile(move_l1);
        writeToFile(msg);
    }
    else if (line == 2){
        writeToFile(move_l2);
        writeToFile(msg);
    }
    else {
        std::cout << "The display only has line 1 or 2!" << std::endl;
    }
    return 1;
}

int CustomerDisplay::sendCommand(std::string command) {
    if (command == "clear all")
        writeToFile(clear);
    else if ( command == "command mode 1")
        writeToFile(set_com_mode);
    else if (command == "clear line")
        writeToFile(clear_line);
    else {
        std::cout << "Command not found!" << std::endl;
    }
    return 0;
}

int CustomerDisplay::readDisplay() {
    return 0;
}

CustomerDisplay::~CustomerDisplay() {

}

int CustomerDisplay::writeToFile(std::string value){
    // Open file
    std::ofstream display( path );
    if(!display.is_open()){
        std::cerr << "Unable to open " << path << std::endl;
        exit (EXIT_FAILURE);
    }

    // Write value
    display << value;
    display.close();
    return 0;
}

int CustomerDisplay::readFromFile(std::string &outputString) {
    // Open file
    std::ifstream display( path );
    if(!display){
        std::cerr << "Unable to open " << path << std::endl;
        exit (EXIT_FAILURE);
    }

    // read value
    display >> outputString;
    display.close();
    return 0;
}

void CustomerDisplay::init() {
    writeToFile(set_com_mode);
    writeToFile(init_display);
}




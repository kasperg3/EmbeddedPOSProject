//
// Created by kasper on 10/4/19.
//

#include "../include/GPIO.h"


GPIO::GPIO() {

}

int GPIO::writeToFile(std::string, std::string){
    return 0;
}

int GPIO::readFromFile(std::string file, std::string &outputString) {
    std::string line;
    std::ifstream inFile(file.c_str());
    if (!inFile) {
        return 1;
    }
    while (getline(inFile, line)) {
        outputString = line;
        return 0;
    }
}

GPIO::GPIO(std::string pinString) : pin_number(pinString) {}

int GPIO::setPinNumber(int) {

}

int GPIO::exportPin() {
    return 0;
}

int GPIO::unexportPin() {
    return 0;
}

int GPIO::setPinDirection(std::string) {
    return 0;
}

int GPIO::setPinValue(std::string) {
    return 0;
}

int GPIO::getPinValue(std::string &) {
    return 0;
}

void GPIO::set(void) {

}

void GPIO::clear(void) {

}

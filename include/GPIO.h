//
// Created by kasper on 10/4/19.
//

#ifndef EMBEDDEDPROJ_GPIO_H
#define EMBEDDEDPROJ_GPIO_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>

class GPIO {
private:
    std::string pin_number;

    int writeToFile(std::string, std::string);
    int readFromFile(std::string, std::string&);

public:
    GPIO();
    GPIO(std::string);

    int setPinNumber(int);
    int exportPin();
    int unexportPin();
    int setPinDirection(std::string);
    int setPinValue(std::string);
    int getPinValue(std::string&);

    void set(void);
    void clear(void);
};


#endif //EMBEDDEDPROJ_GPIO_H



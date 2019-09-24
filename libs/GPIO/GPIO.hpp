//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef PERIPHERALS_GPIO_HPP_
#define PERIPHERALS_GPIO_HPP_

#include <string>

class GPIO
{
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

#endif /* PERIPHERALS_GPIO_HPP_ */

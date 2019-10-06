/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "include/CardReader.h"

#include "libs/GPIO/GPIO.hpp"



int main() {
    CardReader cardReader;
    cardReader.runCardReader();

    return 0;
}

/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "include/CardReader.h"

#include "libs/GPIO/GPIO.hpp"
#include <sys/utsname.h>

int main() {
    struct utsname buffer;

    if (uname(&buffer) != 0) {
        return 1;
    }
    printf("system name = %s\n", buffer.sysname);
    printf("node name   = %s\n", buffer.nodename);
    printf("release     = %s\n", buffer.release);
    printf("version     = %s\n", buffer.version);
    printf("machine     = %s\n", buffer.machine);


    //---------------------- INSERT EXECUTION CODE HERE ----------------------
    //CardReader cardReader;
    //cardReader.runCardReader();

    return 0;
}

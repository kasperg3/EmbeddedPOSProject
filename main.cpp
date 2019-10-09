/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "include/CardReader.h"
#include <sys/utsname.h>
#include "include/GPIO.h"
#include "include/NumpadDriver.h"
#include "include/DisplayDriver.h"
#include <chrono>

int init_main(){
    struct utsname buffer{};
    if (uname(&buffer) != 0) {
        return 1;
    }

    printf("system name = %s\n", buffer.sysname);
    printf("node name   = %s\n", buffer.nodename);
    printf("release     = %s\n", buffer.release);
    printf("version     = %s\n", buffer.version);
    printf("machine     = %s\n", buffer.machine);

    printf("---------------------INIT END----------------------\n");
}

void ledTest(){
    GPIO ledPin("984"); // LED PIN
    ledPin.exportPin();
    ledPin.setPinDirection("out");
    ledPin.set();
    std::string pinValue;
    ledPin.getPinValue(pinValue);
    std::cout << "Led value: " + pinValue << std::endl;
}

void numpadDriverTest(){
    NumpadDriver numpadDriver;
    numpadDriver.init();
    int value;
    while(true){
        value = numpadDriver.check();
        if(value != -1)
            std::cout << "value: " << std::hex << value << std::endl;
    }
}

void displayDriverTest(){

    DisplayDriver displayDriver;
    displayDriver.init();
    displayDriver.clear();
    displayDriver.print(1,"q p");
    displayDriver.print(66, 'W');
    displayDriver.print(5, "HERRO");
}

void numpadToDisplayTest(){
    DisplayDriver displayDriver;
    displayDriver.init();
    displayDriver.clear();

    NumpadDriver numpadDriver;
    numpadDriver.init();

    int value;
    int oldValue= -1;
    while(true){
        value = numpadDriver.check();
        if(value != -1 && oldValue != value){
            if(value > 9)
                displayDriver.print(1, value + 7 + '0'); //Add 7 to reach ascii A
            else
                displayDriver.print(1, value + '0');

            oldValue = value;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    init_main();
    //---------------------- INSERT EXECUTION CODE HERE ----------------------//
    //ledTest();
    //numpadDriverTest();
    //displayDriverTest();
    //numpadToDisplayTest();



    return 0;
}

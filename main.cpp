/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "src/peripherals/CardReader.hpp"
#include <sys/utsname.h>
#include "src/peripherals/GPIO.hpp"
#include "src/peripherals/NumpadDriver.hpp"
#include "src/peripherals/DisplayDriver.hpp"
#include <chrono>
#include "src/peripherals/InputEventDriver.h"

//Thread exercise
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>
#include <cstring>
#include <signal.h>
#include "src/Core.h"
#include "src/tasks/NumpadDriverTask.hpp"
#include "src/tasks/DisplayDriverTask.hpp"
#include "src/state_handling/BombStateMachine.hpp"


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
    //displayDriver.clear();

    displayDriver.print(0,"c");
    displayDriver.print(66, "W");
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
                displayDriver.print(1, "string"); //Add 7 to reach ascii A
            else
                displayDriver.print(1, "value0");

            oldValue = value;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int testPosix(){
    NumpadDriverTask numpadDriverTask;
    //numpadDriverTask.setMessageQueue("/message_queue");

    DisplayDriverTask displayDriverTask;
    //displayDriverTask.setMessageQueue("/message_queue");

    //The input
    NumpadDriver numpadDriver;
    DisplayDriver displayDriver;
    numpadDriver.init();
    displayDriver.init();
    displayDriver.clear();

    pthread_t numpadPublisher;
    pthread_t displayConsumer;

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&numpadPublisher, NULL, reinterpret_cast<void *(*)(void *)>(NumpadDriverTask::taskHandler), &numpadDriver);
    pthread_create(&displayConsumer, NULL, reinterpret_cast<void *(*)(void *)>(DisplayDriverTask::taskHandler), &displayDriver);

    pthread_join(numpadPublisher, NULL);
    pthread_join(displayConsumer, NULL);

}


int theBomb (void)
{
    if ( getuid() )
    {
        // This is a hack. The correct way to do it would be to 'sudo make install' and set up proper permissions to the gpio
        std::cout << "This will only work if you are root!"<< std::endl;
        return -1;
    }

    BombStateMachine bomb;

    bomb.init();
    bomb.start();


    return 0;
}

static const char *const pressType[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
};


void keyboardDriverTest(){

    const char *deviceName = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    InputEventDriver driver = InputEventDriver(deviceName);
    while(true){
        input_event inputEvent = driver.readEvent();
        //Check if it's a keyboard state change event.
        if (inputEvent.type == EV_KEY && inputEvent.value >= 0 && inputEvent.value <= 2)
            printf("%s 0x%04x (%d)\n", pressType[inputEvent.value], (int)inputEvent.code, (int)inputEvent.code);
        fflush(stdout);
    }
}


int main() {
    init_main();
    //---------------------- INSERT EXECUTION CODE HERE ----------------------//
    //ledTest();
    //numpadDriverTest();
    //displayDriverTest();
    //numpadToDisplayTest();
    //exercise1lec5();
    //theBomb();
    //testPosix();
    //keyboardDriverTest();

    return 0;
}

//
// Created by kasper on 11/26/19.
//

#ifndef EMBEDDEDPROJ_INPUTEVENTDRIVER_H
#define EMBEDDEDPROJ_INPUTEVENTDRIVER_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <string>

//LOOK INTO ioctl IF THIS DOES NOT WORK WITH THE OTHER DEVICES

class InputEventDriver {

public:
    InputEventDriver(const char *devicePath);
    input_event readEvent();
private:
    int readCode;
    const char *device; //Device path og keyboard
    void setDevicePath(const char *devicePath);
};

#endif //EMBEDDEDPROJ_INPUTEVENTDRIVER_H

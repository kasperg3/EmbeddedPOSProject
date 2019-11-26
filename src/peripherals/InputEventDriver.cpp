//
// Created by kasper on 11/26/19.
//

#include "InputEventDriver.h"

InputEventDriver::InputEventDriver(const char *devicePath) {
    setDevicePath(devicePath);

    readCode = open(device, O_RDONLY);
    if (readCode == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", device, strerror(errno));
    }
}

void InputEventDriver::setDevicePath(const char* devicePath) {
    device = devicePath;
}

input_event InputEventDriver::readEvent() {
    //Read the path and put into input event
    input_event inputEvent;
    read(readCode, &inputEvent, sizeof inputEvent);
    return inputEvent;
}


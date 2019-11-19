//
// Created by kasper on 10/24/19.
//

#ifndef EMBEDDEDPROJ_DISPLAYDRIVERTASK_HPP
#define EMBEDDEDPROJ_DISPLAYDRIVERTASK_HPP


#include <string>
#include "../peripherals/DisplayDriver.hpp"
#include <utility>
#include "../Core.h"
#include <mqueue.h>
#include <errno.h>
#include <cstring>


class DisplayDriverTask : DisplayDriver{

public:
    std::string message_queue_descriptor;

    void setMessageQueue(std::string);
    static void *taskHandler(DisplayDriverTask *displayDriver);

};


#endif //EMBEDDEDPROJ_DISPLAYDRIVERTASK_HPP

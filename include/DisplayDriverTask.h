//
// Created by kasper on 10/24/19.
//

#ifndef EMBEDDEDPROJ_DISPLAYDRIVERTASK_H
#define EMBEDDEDPROJ_DISPLAYDRIVERTASK_H


#include <string>
#include "DisplayDriver.h"
#include <utility>
#include "../include/Core.h"
#include <mqueue.h>
#include <errno.h>
#include <cstring>


class DisplayDriverTask : DisplayDriver{

public:
    std::string message_queue_descriptor;

    void setMessageQueue(std::string);
    static void *taskHandler(DisplayDriverTask *displayDriver);

};


#endif //EMBEDDEDPROJ_DISPLAYDRIVERTASK_H

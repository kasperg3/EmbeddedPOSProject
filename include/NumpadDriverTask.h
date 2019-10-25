//
// Created by kasper on 10/24/19.
//

#ifndef EMBEDDEDPROJ_NUMPADDRIVERTASK_H
#define EMBEDDEDPROJ_NUMPADDRIVERTASK_H


#include <string>
#include "NumpadDriver.h"
#include <mqueue.h>
#include "../include/Core.h"
#include <thread>


class NumpadDriverTask : NumpadDriver {

public:
    std::string message_queue_descriptor;

    void setMessageQueue(std::string);
    static void *taskHandler(NumpadDriverTask *numpadDriver);
};


#endif //EMBEDDEDPROJ_NUMPADDRIVERTASK_H

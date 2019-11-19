//
// Created by kasper on 10/24/19.
//

#ifndef EMBEDDEDPROJ_NUMPADDRIVERTASK_HPP
#define EMBEDDEDPROJ_NUMPADDRIVERTASK_HPP


#include <string>
#include "../peripherals/NumpadDriver.hpp"
#include <mqueue.h>
#include "../Core.h"
#include <thread>


class NumpadDriverTask : NumpadDriver {

public:
    std::string message_queue_descriptor;

    void setMessageQueue(std::string);
    static void *taskHandler(NumpadDriverTask *numpadDriver);
};


#endif //EMBEDDEDPROJ_NUMPADDRIVERTASK_HPP

//
// Created by troel on 12/28/19.
//

#ifndef EMBEDDEDPROJ_CUSTOMERDISPLAYTASK_HPP
#define EMBEDDEDPROJ_CUSTOMERDISPLAYTASK_HPP

#include <string>
#include "../peripherals/CustomerDisplay.hpp"
#include <utility>
#include <mqueue.h>
#include "../Core.h"
#include "../utilities/queue.h"
#include <thread>
#include <errno.h>
#include <cstring>


class CustomerDisplayTask : CustomerDisplay {

public:
    std::string message_queue_descriptor;

    void setMessageQueue(std::string);
    static void *taskHandler(CustomerDisplayTask *customerDisplay);

private:

};


#endif //EMBEDDEDPROJ_CUSTOMERDISPLAYTASK_HPP

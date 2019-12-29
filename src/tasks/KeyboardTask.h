//
// Created by kasper on 12/28/19.
//

#ifndef EMBEDDEDPROJ_KEYBOARDTASK_H
#define EMBEDDEDPROJ_KEYBOARDTASK_H

#include <string>
#include "../peripherals/InputEventDriver.h"
#include <mqueue.h>
#include "../Core.h"
#include <thread>

class KeyboardTask : InputEventDriver{

public:
    static void *taskHandler(KeyboardTask *keyboardTask);

};


#endif //EMBEDDEDPROJ_KEYBOARDTASK_H

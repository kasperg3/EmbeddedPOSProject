//
// Created by kasper on 12/28/19.
//

#ifndef EMBEDDEDPROJ_CARDREADERTASK_H
#define EMBEDDEDPROJ_CARDREADERTASK_H

#include <string>
#include "../peripherals/InputEventDriver.h"
#include <mqueue.h>
#include "../Core.h"
#include <thread>
#include <iostream>

class CardReaderTask : InputEventDriver{

public:
    static void *taskHandler(CardReaderTask *cardReaderTask);
};


#endif //EMBEDDEDPROJ_CARDREADERTASK_H

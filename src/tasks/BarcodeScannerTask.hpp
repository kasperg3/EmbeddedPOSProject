//
// Created by kasper on 12/28/19.
//

#ifndef EMBEDDEDPROJ_BARCODESCANNERTASK_H
#define EMBEDDEDPROJ_BARCODESCANNERTASK_H

#include <string>
#include "../peripherals/InputEventDriver.h"
#include <mqueue.h>
#include "../Core.h"
#include <thread>
#include <iostream>

class BarcodeScannerTask : InputEventDriver{

public:
    static void *taskHandler(BarcodeScannerTask *barcodeDriver);
};


#endif //EMBEDDEDPROJ_BARCODESCANNERTASK_H

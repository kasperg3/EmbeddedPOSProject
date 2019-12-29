//
// Created by nikolaj on 12/29/19.
//

#ifndef EMBEDDEDPROJ_RECEIPTPRINTERTASK_HPP
#define EMBEDDEDPROJ_RECEIPTPRINTERTASK_HPP

#include <string>
#include "../database/receipt.hpp"
#include <mqueue.h>
#include "../Core.h"
#include <thread>
#include <iostream>

class ReceiptPrinterTask : Receipt{

public:
    static void *taskHandler(ReceiptPrinterTask *Receipt);
};




#endif //EMBEDDEDPROJ_RECEIPTPRINTERTASK_HPP

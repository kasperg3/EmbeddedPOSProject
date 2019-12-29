//
// Created by kasper on 12/28/19.
//

#include "BarcodeScannerTask.hpp"
#include "../utilities/queue.h"


void *BarcodeScannerTask::taskHandler(BarcodeScannerTask *barcodeDriver) {

    Queue queue(QUEUE_BARCODE, O_CREAT | O_WRONLY, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE);

    char buffer[QUEUE_BARCODE_MSGSIZE] = "";
    memset(buffer, 0, sizeof(buffer));   //Removes data on the allocated buffer
    int charCounter = 0;                   //Initializes the char pointer
    while(true) {
        input_event inputEvent = barcodeDriver->readEvent();
        if (inputEvent.value == 1) {
            if (inputEvent.code != 28) {
                buffer[charCounter] = *key_names[inputEvent.code];
                charCounter++;
            } else {
                printf("[BarcocdeScanner] Read card with code: %s \n", buffer);
                queue.send(buffer);
                memset(buffer, 0, sizeof buffer);   //Removes data on the allocated buffer
                charCounter = 0;
            }
            fflush(stdout);
        }
    }
    return nullptr;
}

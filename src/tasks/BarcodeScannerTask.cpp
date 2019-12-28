//
// Created by kasper on 12/28/19.
//

#include "BarcodeScannerTask.hpp"


void *BarcodeScannerTask::taskHandler(BarcodeScannerTask *barcodeDriver) {
    mq_unlink(QUEUE_BARCODE);

    /* Create a Queue and wait for it to be created */
    struct mq_attr attr;
    mqd_t mq;
    memset( &attr, 0x00, sizeof(struct mq_attr) );
    attr.mq_maxmsg = QUEUE_BARCODE_MAXMSG;
    attr.mq_msgsize = QUEUE_BARCODE_MSGSIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    do {
        mq = mq_open(QUEUE_BARCODE, O_CREAT | O_WRONLY, QUEUE_BARCODE_PERMS, &attr);
        if(mq < 0) {
            printf("[BarcocdeScanner]: The queue is not created yet. Waiting...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(mq == -1);
    printf("[BarcocdeScanner]: Queue opened, queue descriptor: %d.\n", mq);
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
                if(mq_send(mq, buffer, QUEUE_BARCODE_MSGSIZE, 0) < 0) {
                    printf("[BarcocdeScanner]: CANNOT SEND MESSAGE \n");
                    std::cout <<  strerror(errno) << std::endl;
                }
                memset(buffer, 0, sizeof buffer);   //Removes data on the allocated buffer
                charCounter = 0;
            }
            fflush(stdout);
        }
    }
    /* Cleanup */
    printf("[BarcocdeScanner]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_BARCODE);

    return nullptr;
}

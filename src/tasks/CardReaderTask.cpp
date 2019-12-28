//
// Created by kasper on 12/28/19.
//

#include "CardReaderTask.hpp"

void *CardReaderTask::taskHandler(CardReaderTask *cardReaderTask) {
    mq_unlink(QUEUE_BARCODE);

    /* Create a Queue and wait for it to be created */
    struct mq_attr attr;
    mqd_t mq;
    memset( &attr, 0x00, sizeof(struct mq_attr) );
    attr.mq_maxmsg = QUEUE_CARDREADER_MAXMSG;
    attr.mq_msgsize = QUEUE_CARDREADER_MSGSIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    do {
        mq = mq_open(QUEUE_CARDREADER, O_CREAT | O_WRONLY, QUEUE_CARDREADER_PERMS, &attr);
        if(mq < 0) {
            printf("[CardReader]: The queue is not created yet. Waiting...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(mq == -1);
    printf("[CardReader]: Queue opened, queue descriptor: %d.\n", mq);
    char buffer[QUEUE_CARDREADER_MSGSIZE] = "";
    memset(buffer, 0, sizeof(buffer));   //Removes data on the allocated buffer
    int charCounter = 0;                   //Initializes the char pointer
    while(true) {
        input_event inputEvent = cardReaderTask->readEvent();

        if (inputEvent.value == 1) {
            printf("Value: %s \t Code: 0x%04x (%s) \t Type: %d \n", pressType[inputEvent.value], (int)inputEvent.code, key_names[(int)inputEvent.code], inputEvent.type);
            if (inputEvent.code != 28) {
                buffer[charCounter] = *key_names[inputEvent.code];
                charCounter++;
            } else {
                printf("[CardReader] Scanned item with code: %s \n", buffer);
                if(mq_send(mq, buffer, QUEUE_CARDREADER_MSGSIZE, 0) < 0) {
                    std::cout <<  strerror(errno) << std::endl;
                    printf("[CardReader]: CANNOT SEND MESSAGE \n");
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

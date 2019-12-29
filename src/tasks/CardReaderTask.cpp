//
// Created by kasper on 12/28/19.
//

#include "CardReaderTask.hpp"

void *CardReaderTask::taskHandler(CardReaderTask *cardReaderTask) {
    mq_unlink(QUEUE_CARDREADER);

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
            printf("[Cardreader]: The queue is not created yet. Waiting...\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } while(mq == -1);
    printf("[Cardreader]: Queue opened, queue descriptor: %d.\n", mq);
    char buffer[QUEUE_CARDREADER_MSGSIZE] = "";
    memset(buffer, 0, sizeof(buffer));   //Removes data on the allocated buffer
    int charCounter = 0;                    //Initializes the char pointer
    bool startReading = false;
    while(true) {
        input_event inputEvent = cardReaderTask->readEvent();
        if (inputEvent.value == 1) {
            if (charCounter < QUEUE_CARDREADER_MSGSIZE) {
                if(startReading){
                    buffer[charCounter] = *key_names[inputEvent.code];
                    charCounter++;
                }
                if(inputEvent.code == 48){ //The character before the cardnumber
                    startReading = true;
                }
            } else {
                if(mq_send(mq, buffer, QUEUE_CARDREADER_MSGSIZE, 0) < 0) {
                    printf("[Cardreader]: CANNOT SEND MESSAGE, %s \n", strerror(errno));
                }
                printf("[Cardreader] Read card with code: %s \n", buffer);
                memset(buffer, 0, sizeof buffer);   //Removes data on the allocated buffer
                charCounter = 0;
                startReading = false;
            }
            fflush(stdout);
        }
    }
    /* Cleanup */
    printf("[Cardreader]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_CARDREADER);

    return nullptr;
}

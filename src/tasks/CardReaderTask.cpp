//
// Created by kasper on 12/28/19.
//

#include "CardReaderTask.hpp"
#include "../utilities/queue.h"

void *CardReaderTask::taskHandler(CardReaderTask *cardReaderTask) {

    Queue queue(QUEUE_CARDREADER, O_CREAT | O_WRONLY, QUEUE_CARDREADER_MAXMSG, QUEUE_CARDREADER_MSGSIZE);

    char buffer[QUEUE_CARDREADER_MSGSIZE];
    memset(buffer, 0, sizeof(buffer));   //Removes data on the allocated buffer
    int charCounter = 0;                    //Initializes the char pointer
    bool startReading = false;
    while(true) {
        input_event inputEvent = cardReaderTask->readEvent();
        if (inputEvent.value == 1) {
            if (charCounter < QUEUE_CARDREADER_MSGSIZE-1) {
                if(startReading){
                    buffer[charCounter] = *key_names[inputEvent.code];
                    charCounter++;
                }
                if(inputEvent.code == 48){ //The character before the cardnumber
                    startReading = true;
                }
            } else {
                queue.send(buffer);
                printf("[Cardreader] Read card with code: %s \n", buffer);
                memset(buffer, 0, sizeof buffer);   //Removes data on the allocated buffer
                charCounter = 0;
                startReading = false;
            }
            fflush(stdout);
        }
    }
    return nullptr;
}

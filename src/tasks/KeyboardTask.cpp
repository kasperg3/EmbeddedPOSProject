//
// Created by kasper on 12/28/19.
//

#include "KeyboardTask.h"
#include "../utilities/queue.h"

void *KeyboardTask::taskHandler(KeyboardTask *keyboardTask) {
    //Create The queue
    Queue queue(QUEUE_KEYBOARD, O_CREAT | O_WRONLY, QUEUE_KEYBOARD_MAXMSG, QUEUE_KEYBOARD_MSGSIZE);
    char buffer[QUEUE_KEYBOARD_MSGSIZE] = "";
    memset(buffer, 0, sizeof(buffer));   //Removes data on the allocated buffer

    char *currentKey;
    while(true) {
        input_event inputEvent = keyboardTask->readEvent();
        if (inputEvent.value == 1) {
            currentKey = key_names[inputEvent.code];
            strcpy(buffer, currentKey);
            printf("[Keyboard] Buffer content: %s , length: %i \n", buffer, sizeof(buffer)); //Used for debugging
            queue.send(buffer);
            memset(buffer, 0, sizeof buffer);   //Removes data on the allocated buffer
            fflush(stdout);
        }
    }
    return nullptr;
}

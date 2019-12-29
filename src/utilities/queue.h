#ifndef QUEUE_H
#define QUEUE_H

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include "errno.h"

#include <string>
#include <iostream>

class Queue
{
public:
    Queue(const char *queue_name, int flags);
    Queue(const char* queue_name, int flags, int maxmsg, int msgsize);

    bool empty();
    void send(std::string message);
    void send(char *message);
    std::string receive();
    void flush();

    const char* queue_name;
    mqd_t queue_handle;
    struct mq_attr queue_attributes;

    ~Queue();

};



#endif // QUEUE_H

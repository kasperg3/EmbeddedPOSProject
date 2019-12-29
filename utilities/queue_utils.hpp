#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#include <string>
#include <iostream>

mqd_t create_queue(const char *queue_name, int maxmsg, int msgsize);

void send_message_to_queue(const char* queue_name, std::string message);

std::string receive_message_from_queue(const char* queue_name);

bool queue_is_empty(const char* queue_name);

void flush_queue(const char* queue_name);

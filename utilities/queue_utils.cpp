#include "queue_utils.hpp"

using namespace std;


mqd_t create_queue(const char *queue_name, int maxmsg, int msgsize)
{
    mq_unlink(queue_name);
    mode_t permissions = 0644;
    struct mq_attr attributes;
    attributes.mq_maxmsg = maxmsg;
    attributes.mq_msgsize = msgsize;

    mqd_t queue_handle = mq_open(queue_name, O_CREAT, permissions, &attributes);
    if(queue_handle == (mqd_t) -1)
    {
        printf("Could not create queue %s - %s\n", queue_name, strerror(errno));
        return -1;
    }

    return queue_handle;
}


void send_message_to_queue(const char* queue_name, string message)
{
    mqd_t queue_handle = mq_open(queue_name, O_WRONLY | O_NONBLOCK);
    struct mq_attr attributes;
    mq_getattr(queue_handle, &attributes);

    if(mq_send(queue_handle, message.c_str(), attributes.mq_msgsize, 0) == -1)
        printf("Could not send to queue %s - %s\n", queue_name, strerror(errno));

    mq_close(queue_handle);
}

string receive_message_from_queue(const char* queue_name)
{
    mqd_t queue_handle = mq_open(queue_name, O_RDONLY | O_NONBLOCK);
    struct mq_attr attributes;
    mq_getattr(queue_handle, &attributes);

    char* message = new char[attributes.mq_msgsize];

    if(mq_receive(queue_handle, message, attributes.mq_msgsize, NULL) == -1)
        printf("Could not receive from queue %s - %s\n", queue_name, strerror(errno));

    string string_message(message);
    delete message;
    mq_close(queue_handle);

    return string_message;
}


bool queue_is_empty(const char *queue_name)
{
    mqd_t queue_handle = mq_open(queue_name, O_RDONLY);
    struct mq_attr attributes;
    mq_getattr(queue_handle, &attributes);

    mq_close(queue_handle);

    return !attributes.mq_curmsgs;
}

void flush_queue(const char *queue_name)
{
    mqd_t queue_handle = mq_open(queue_name, O_RDONLY);
    struct mq_attr attributes;
    mq_getattr(queue_handle, &attributes);

    char* dummy_string = new char[attributes.mq_msgsize];

    for(int i = 0; i < attributes.mq_curmsgs; i++)
        mq_receive(queue_handle, dummy_string, attributes.mq_msgsize, NULL);

    delete dummy_string;
}





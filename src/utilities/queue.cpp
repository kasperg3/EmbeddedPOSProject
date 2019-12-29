#include "queue.h"

using namespace std;

Queue::Queue(const char *queue_name, int flags)
{
    this->queue_name = queue_name;
    queue_handle = mq_open(queue_name, flags);
    if(queue_handle == (mqd_t) -1)
        printf("Could not open queue %s - %s\n", queue_name, strerror(errno));
}

Queue::Queue(const char *queue_name, int flags, int maxmsg, int msgsize)
{
    this->queue_name = queue_name;
    mq_unlink(queue_name);
    mode_t permissions = 0644;

    queue_attributes.mq_maxmsg = maxmsg;
    queue_attributes.mq_msgsize = msgsize;

    queue_handle = mq_open(queue_name, O_CREAT | flags, permissions, &queue_attributes);
    if(queue_handle == (mqd_t) -1)
        printf("Could not create queue %s - %s\n", queue_name, strerror(errno));
}

bool Queue::empty()
{
    mq_getattr(queue_handle, &queue_attributes);

    return !queue_attributes.mq_curmsgs;
}

void Queue::send(std::string message)
{
    mq_getattr(queue_handle, &queue_attributes);

    if(mq_send(queue_handle, message.c_str(), queue_attributes.mq_msgsize, 0) == -1)
        printf("Could not send to queue %s - %s\n", queue_name, strerror(errno));
}

std::string Queue::receive()
{
    mq_getattr(queue_handle, &queue_attributes);

    char* message = new char[queue_attributes.mq_msgsize];

    if(mq_receive(queue_handle, message, queue_attributes.mq_msgsize, NULL) == -1)
        printf("Could not receive from queue %s - %s\n", queue_name, strerror(errno));

    string string_message(message);
    delete message;

    return string_message;
}

void Queue::flush()
{
    mqd_t handle = mq_open(queue_name, O_RDONLY);   //To allow 'O_WRONLY' queues to flush
    struct mq_attr attributes;                      //Because this function uses mq_receive
    mq_getattr(handle, &attributes);                //which only works with read permissions

    char* dummy_string = new char[attributes.mq_msgsize];

    for(int i = 0; i < attributes.mq_curmsgs; i++)
        mq_receive(handle, dummy_string, attributes.mq_msgsize, NULL);

    mq_close(handle);
    delete dummy_string;
}



Queue::~Queue()
{
    mq_close(queue_handle);
}

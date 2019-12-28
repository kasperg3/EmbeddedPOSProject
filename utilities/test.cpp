#include "queue_utils.hpp"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <string.h>

#include <iostream>

using namespace std;

const int MAXMSG = 10;
const int MSGSIZE = 1024;
const char* queue_name = "/test_queue";

int main(int argc, char* argv[])
{
    create_queue(queue_name, MAXMSG, MSGSIZE);
//    create_queue("/another_queue", 5, 100);

    for(int i = 0; i < 8; i++)
        send_message_to_queue(queue_name, "hellofellow" + to_string(i));

    for(int i = 0; i < 5; i++)
        cout << receive_message_from_queue(queue_name) << endl;

    flush_queue(queue_name);

    if(queue_is_empty(queue_name))
        cout << "The queue is empty" << endl;

	return 0;
}

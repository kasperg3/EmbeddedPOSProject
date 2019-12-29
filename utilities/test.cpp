#include "queue_utils.hpp"
#include "queue.h"

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

    Queue q(queue_name, 0, MAXMSG, MSGSIZE);
    Queue q2(queue_name, O_WRONLY);
    Queue q3(queue_name, O_RDONLY);

    for(int i = 0; i < 8; i++)
        q2.send("hellofellow" + to_string(i));

    for(int i = 0; i < 5; i++)
        cout << q3.receive() << endl;

    //q.flush();
    //q2.flush();
    q3.flush();

    if(q2.empty())
        cout << "The queue is empty" << endl;

	return 0;
}

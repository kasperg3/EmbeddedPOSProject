#include <zmq.hpp>
#include <string>
#include "CustomerDisplay.hpp"
#include "../Core.h"

using namespace std;

int main()
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://" + PC_IP + ":" + CUSTOMER_DISPLAY_PORT);

    CustomerDisplay cd;

    while(true)
    {
        zmq::message_t request;

        socket.recv(&request);
        string message_buffer((const char*)request.data(), request.size());
        printf("Customer Display Task received: %s\n", message_buffer.data());
        fflush(stdout);
        cd.print(1,message_buffer);

        zmq::message_t reply;
        memcpy(reply.data(), "Printed", 7);
        socket.send(reply);
    }

    return 0;
}

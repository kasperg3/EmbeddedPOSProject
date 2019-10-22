/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "include/CardReader.h"
#include <sys/utsname.h>
#include "include/GPIO.h"
#include "include/NumpadDriver.h"
#include "include/DisplayDriver.h"
#include <chrono>

//Thread exercise
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>
#include <cstring>
#include <signal.h>
#include "include/Core.h"

int init_main(){
    struct utsname buffer{};
    if (uname(&buffer) != 0) {
        return 1;
    }

    printf("system name = %s\n", buffer.sysname);
    printf("node name   = %s\n", buffer.nodename);
    printf("release     = %s\n", buffer.release);
    printf("version     = %s\n", buffer.version);
    printf("machine     = %s\n", buffer.machine);

    printf("---------------------INIT END----------------------\n");
}

void ledTest(){
    GPIO ledPin("984"); // LED PIN
    ledPin.exportPin();
    ledPin.setPinDirection("out");
    ledPin.set();
    std::string pinValue;
    ledPin.getPinValue(pinValue);
    std::cout << "Led value: " + pinValue << std::endl;
}

void numpadDriverTest(){
    NumpadDriver numpadDriver;
    numpadDriver.init();
    int value;
    while(true){
        value = numpadDriver.check();
        if(value != -1)
            std::cout << "value: " << std::hex << value << std::endl;
    }
}

void displayDriverTest(){

    DisplayDriver displayDriver;
    displayDriver.init();
    displayDriver.clear();
    displayDriver.print(1,"q p");
    displayDriver.print(66, 'W');
    displayDriver.print(5, "HERRO");
}

void numpadToDisplayTest(){
    DisplayDriver displayDriver;
    displayDriver.init();
    displayDriver.clear();

    NumpadDriver numpadDriver;
    numpadDriver.init();

    int value;
    int oldValue= -1;
    while(true){
        value = numpadDriver.check();
        if(value != -1 && oldValue != value){
            if(value > 9)
                displayDriver.print(1, value + 7 + '0'); //Add 7 to reach ascii A
            else
                displayDriver.print(1, value + '0');

            oldValue = value;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

//EXERCISE LECTURE 5 - POSIX
pthread_mutex_t stopMutex;
static bool th_consumer_running = true;
static bool th_publisher_running = true;

void signal_handler(int signum) {
    fprintf(stderr, "\n\nReceived signal: %d.\nStopping threads...\n", signum);
    th_consumer_running = false;
    th_publisher_running = false;
}

int counter = 0;
void *print_number(void *threadid){
    for(int i = 0; i < 500; i++){
        pthread_mutex_lock(&stopMutex);
        counter++;
        std::cout << counter << std::endl;
        pthread_mutex_unlock(&stopMutex);
    }
}


void *queue_consumer(void *args){
    (void) args; /* Suppress -Wunused-parameter warning. */
    /* Initialize the queue attributes */
    struct mq_attr attr = QUEUE_ATTR_INITIALIZER;

    /* Create the message queue. The queue reader is NONBLOCK. */
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, QUEUE_PERMS, &attr);
    if(mq < 0) {
        fprintf(stderr, "[CONSUMER]: Error, cannot open the queue: %s.\n", strerror(errno));
        exit(1);
    }

    printf("[CONSUMER]: Queue opened, queue descriptor: %d.\n", mq);

    unsigned int prio;
    ssize_t bytes_read;
    char buffer[QUEUE_MSGSIZE + 1];
    struct timespec poll_sleep;
    while(th_consumer_running) {
        memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, QUEUE_MSGSIZE, &prio);
        if(bytes_read >= 0) {
            printf("[CONSUMER]: Received message: \"%s\"\n", buffer);
        } else {//Wait for messages
            printf("[CONSUMER]: No messages yet.\n");
            poll_sleep = QUEUE_POLL_CONSUMER;
            nanosleep(&poll_sleep, NULL);
        }
        fflush(stdout);
    }

    /* Cleanup */
    printf("[CONSUMER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return NULL;
}

void *queue_publisher(void *args){
    (void) args; /* Suppress -Wunused-parameter warning. */
    /* Open the created queue by the consumer. */
    mqd_t mq;
    struct timespec poll_sleep;
    do {
        mq = mq_open(QUEUE_NAME, O_WRONLY);
        if(mq < 0) {
            printf("[PUBLISHER]: The queue is not created yet. Waiting...\n");
            poll_sleep = QUEUE_POLL_PUBLISHER;
            nanosleep(&poll_sleep, NULL);
        }
    } while(mq == -1);

    printf("[PUBLISHER]: Queue opened, queue descriptor: %d.\n", mq);

    unsigned int prio = 0;
    int count = 1;
    char buffer[QUEUE_MSGSIZE];
    while(th_publisher_running) {//PRODUCE Messages
        /* Send a burst of three messages */
        for(int i=0; i<3; i++) {
            snprintf(buffer, sizeof(buffer), "put msg here");
            printf("[PUBLISHER]: Sending message %d ...\n", count, 0);
            mq_send(mq, buffer, QUEUE_MSGSIZE, 0);
            count++;
        }

        poll_sleep = QUEUE_POLL_PUBLISHER;
        nanosleep(&poll_sleep, NULL);

        fflush(stdout);
    }

    /* Cleanup */
    printf("[PUBLISHER]: Cleanup...\n");
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return NULL;
}

int exercise1lec5(){
    pthread_t th_publisher, th_consumer;

    signal(SIGINT, signal_handler);

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    printf("Start...\n");

    pthread_create(&th_consumer, NULL, &queue_consumer, NULL);
    pthread_create(&th_publisher, NULL, &queue_publisher, NULL);

    pthread_join(th_publisher, NULL);
    pthread_join(th_consumer, NULL);

    printf("Done...\n");

    return (EXIT_SUCCESS);
}

int main() {
    init_main();
    //---------------------- INSERT EXECUTION CODE HERE ----------------------//
    //ledTest();
    //numpadDriverTest();
    //displayDriverTest();
    //numpadToDisplayTest();

    exercise1lec5();

    return 0;
}

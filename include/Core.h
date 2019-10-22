//
// Created by kasper on 10/22/19.
//

#ifndef EMBEDDEDPROJ_CORE_H
#define EMBEDDEDPROJ_CORE_H

#define QUEUE_NAME  "/test_queue" /* Queue name. */
#define QUEUE_PERMS ((int)(0644))
#define QUEUE_MAXMSG  16 /* Maximum number of messages. */
#define QUEUE_MSGSIZE 128 /* Length of message. */
#define QUEUE_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_MAXMSG, QUEUE_MSGSIZE, 0, {0}})

/* The consumer is faster than the publisher. */
#define QUEUE_POLL_CONSUMER ((struct timespec){2, 500000000})
#define QUEUE_POLL_PUBLISHER ((struct timespec){5, 0})


#endif //EMBEDDEDPROJ_CORE_H

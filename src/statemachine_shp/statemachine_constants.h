//NumpadDriver QUEUE Defines
#define QUEUE_NUMPAD  "/numpad_queue" /* Queue name. */
#define QUEUE_NUMPAD_PERMS ((int)(0644))
#define QUEUE_NUMPAD_MAXMSG  10 /* Maximum number of messages. */
#define QUEUE_NUMPAD_MSGSIZE 1 /* Length of message. */
#define QUEUE_NUMPAD_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_NUMPAD_MAXMSG, QUEUE_NUMPAD_MSGSIZE, 0, {0}})

//BarcodeScanner QUEUE Defines
#define QUEUE_BARCODE  "/barcode_queue" /* Queue name. */
#define QUEUE_BARCODE_PERMS ((int)(0644))
#define QUEUE_BARCODE_MAXMSG  10 /* Maximum number of messages. */
#define QUEUE_BARCODE_MSGSIZE 14 /* Length of message. */
#define QUEUE_BARCODE_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE, 0, {0}})

//CardReader QUEUE Defines
#define QUEUE_CARDREADER  "/cardreader_queue" /* Queue name. */
#define QUEUE_CARDREADER_PERMS ((int)(0644))
#define QUEUE_CARDREADER_MAXMSG  10 /* Maximum number of messages. */
#define QUEUE_CARDREADER_MSGSIZE 17 /* Length of message. */
#define QUEUE_CARDREADER_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE, 0, {0}})
#define QUEUE_NAME  "/test_queue" /* Queue name. */
#define CD_QUEUE_PERMS ((int)(0644))
#define CD_QUEUE_MAXMSG  10 /* Maximum number of messages. */
#define CUSTOMER_DISPLAY_QUEUE_NAME "/cd_queue" /* Customer queue display name */
#define CD_QUEUE_MSGSIZE 128 /* Length of message. */
#define CD_QUEUE_ATTR_INITIALIZER ((struct mq_attr){0, CD_QUEUE_MAXMSG, CD_QUEUE_MSGSIZE, 0, {0}})


//KeyBoard QUEUE Defines
#define QUEUE_KEYBOARD  "/keyboard_queue" /* Queue name. */
#define QUEUE_KEYBOARD_MAXMSG  10 /* Maximum number of messages. */
#define QUEUE_KEYBOARD_MSGSIZE 8 /* Length of message. */

/* The consumer is faster than the publisher. */
#define QUEUE_POLL_CONSUMER ((struct timespec){2, 500000000})
#define QUEUE_POLL_PUBLISHER ((struct timespec){5, 0})

#define QUEUE_RECEIPT  "/receipt_queue" /* Queue name. */
#define QUEUE_RECEIPT_PERMS ((int)(0644))
#define QUEUE_RECEIPT_MAXMSG  5 /* Maximum number of messages. */
#define QUEUE_RECEIPT_MSGSIZE 2050 /* Length of message. Shouldn't be longer than this 10 items with max 20 chars per line*/
#define QUEUE_RECEIPT_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_RECEIPT_MAXMSG, QUEUE_RECEIPT_MSGSIZE, 0, {0}})


#include <string>
const std::string PC_IP = "10.42.0.1";
const std::string CUSTOMER_DISPLAY_PORT = "1337";

enum {NO_EVENT, EVENT_BARCODE_SCANNED, EVENT_KEYBOARD_PRESSED, EVENT_CARD_READ};
enum {STATE_SCAN, STATE_MULTIPLY_GOODS, STATE_PAY};

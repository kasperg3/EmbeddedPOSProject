//
// Created by kasper on 10/22/19.
//

#ifndef EMBEDDEDPROJ_CORE_H
#define EMBEDDEDPROJ_CORE_H

//Device Paths


#define BARCODE_SCANNER_PATH "/dev/input/by-id/usb-USB_Adapter_USB_Device-event-kbd"; //Scanner
#define CARDREADER_PATH "/dev/input/by-id/usb-c216_0180-event-if00";//Card Reader
//#define KEYBOARD_PATH "/dev/input/by-path/platform-i8042-serio-0-event-kbd"; //Keyboard Kasper pc
#define KEYBOARD_PATH "/dev/input/by-id/usb-SEM_USB_Keyboard-event-kbd"; //Keyboard zybo

//InputEvent types
static const char *const pressType[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
};

#include <linux/input.h>
#define UNKNOWN_KEY ""
#define UK UNKNOWN_KEY

/*
 * Keymapping from
 */
static char *key_names[] = {
        UK, "<ESC>",
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
        "<Backspace>", "<Tab>",
        "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
        "[", "]", "<Enter>", "<LCtrl>",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
        "'", "`", "<LShift>",
        "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
        "<RShift>",
        "<KP*>",
        "<LAlt>", " ", "<CapsLock>",
        "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
        "<NumLock>", "<ScrollLock>",
        "<KP7>", "<KP8>", "<KP9>",
        "<KP->",
        "<KP4>", "<KP5>", "<KP6>",
        "<KP+>",
        "<KP1>", "<KP2>", "<KP3>", "<KP0>",
        "<KP.>",
        UK, UK, UK,
        "<F11>", "<F12>",
        UK, UK, UK, UK, UK, UK, UK,
        "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
        "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
        "<PageDown>", "<Insert>", "<Delete>"
};

static char *shift_key_names[] = {
        UK, "<ESC>",
        "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
        "<Backspace>", "<Tab>",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "{", "}", "<Enter>", "<LCtrl>",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
        "\"", "~", "<LShift>",
        "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
        "<RShift>",
        "<KP*>",
        "<LAlt>", " ", "<CapsLock>",
        "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
        "<NumLock>", "<ScrollLock>",
        "<KP7>", "<KP8>", "<KP9>",
        "<KP->",
        "<KP4>", "<KP5>", "<KP6>",
        "<KP+>",
        "<KP1>", "<KP2>", "<KP3>", "<KP0>",
        "<KP.>",
        UK, UK, UK,
        "<F11>", "<F12>",
        UK, UK, UK, UK, UK, UK, UK,
        "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
        "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
        "<PageDown>", "<Insert>", "<Delete>"
};


#undef UK

//NumpadDriver QUEUE Defines
#define QUEUE_NUMPAD  "/numpad_queue" /* Queue name. */
#define QUEUE_NUMPAD_PERMS ((int)(0644))
#define QUEUE_NUMPAD_MAXMSG  16 /* Maximum number of messages. */
#define QUEUE_NUMPAD_MSGSIZE 1 /* Length of message. */
#define QUEUE_NUMPAD_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_NUMPAD_MAXMSG, QUEUE_NUMPAD_MSGSIZE, 0, {0}})

//BarcodeScanner QUEUE Defines
#define QUEUE_BARCODE  "/barcode_queue" /* Queue name. */
#define QUEUE_BARCODE_PERMS ((int)(0644))
#define QUEUE_BARCODE_MAXMSG  16 /* Maximum number of messages. */
#define QUEUE_BARCODE_MSGSIZE 14 /* Length of message. */
#define QUEUE_BARCODE_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE, 0, {0}})

//CardReader QUEUE Defines
#define QUEUE_CARDREADER  "/cardreader_queue" /* Queue name. */
#define QUEUE_CARDREADER_PERMS ((int)(0644))
#define QUEUE_CARDREADER_MAXMSG  20 /* Maximum number of messages. */
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
#define QUEUE_KEYBOARD_MAXMSG  16 /* Maximum number of messages. */
#define QUEUE_KEYBOARD_MSGSIZE 8 /* Length of message. */

/* The consumer is faster than the publisher. */
#define QUEUE_POLL_CONSUMER ((struct timespec){2, 500000000})
#define QUEUE_POLL_PUBLISHER ((struct timespec){5, 0})

#define QUEUE_RECEIPT  "/receipt_queue" /* Queue name. */
#define QUEUE_RECEIPT_PERMS ((int)(0644))
#define QUEUE_RECEIPT_MAXMSG  5 /* Maximum number of messages. */
#define QUEUE_RECEIPT_MSGSIZE 2050 /* Length of message. Shouldn't be longer than this 10 items with max 20 chars per line*/
#define QUEUE_RECEIPT_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_RECEIPT_MAXMSG, QUEUE_RECEIPT_MSGSIZE, 0, {0}})

static bool th_consumer_running = true;
static bool th_publisher_running = true;


#endif //EMBEDDEDPROJ_CORE_H
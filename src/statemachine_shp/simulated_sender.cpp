#include "queue.h"

#include <iostream>
#include <unistd.h>
#include "statemachine_constants.h"
using namespace std;

int main()
{
    Queue barcode_queue(QUEUE_BARCODE, O_WRONLY | O_NONBLOCK);
    Queue keyboard_queue(QUEUE_KEYBOARD, O_WRONLY | O_NONBLOCK);
    Queue card_reader_queue(QUEUE_CARDREADER, O_WRONLY| O_NONBLOCK);
    Queue numpad_queue(QUEUE_NUMPAD, O_WRONLY | O_NONBLOCK);

    Queue lcd_queue(QUEUE_LCD, O_RDONLY);
    Queue receipt_queue(QUEUE_RECEIPT, O_RDONLY);

    barcode_queue.flush();
    keyboard_queue.flush();
    card_reader_queue.flush();


//    barcode_queue.send("5000159461123");
//    sleep(3);
//    keyboard_queue.send("ESC");
//    sleep(3);
    keyboard_queue.send("1");
    sleep(3);
    keyboard_queue.send("5");
    sleep(3);
    barcode_queue.send("5701115667007");
    sleep(3);
    keyboard_queue.send("<ENTER>");



    return 0;
}



#include "db_interface.hpp"
#include "queue.h"
#include "shpstatemachine.h"

#include <iostream>

using namespace std;

void create_mqueues();

int main()
{
    create_mqueues();

    ShpStateMachine sm;
    sm.run();

    return 0;
}

void create_mqueues()
{
    Queue barcode_queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK, QUEUE_BARCODE_MAXMSG, QUEUE_BARCODE_MSGSIZE);
    Queue keyboard_queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK, QUEUE_KEYBOARD_MAXMSG, QUEUE_KEYBOARD_MSGSIZE);
    Queue card_reader_queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK, QUEUE_CARDREADER_MAXMSG, QUEUE_CARDREADER_MSGSIZE);
    Queue numpad_queue(QUEUE_NUMPAD, O_RDONLY | O_NONBLOCK, QUEUE_NUMPAD_MAXMSG, QUEUE_NUMPAD_MSGSIZE);

    Queue receipt_queue(QUEUE_RECEIPT, O_WRONLY, QUEUE_RECEIPT_MAXMSG, QUEUE_RECEIPT_MSGSIZE);
    Queue lcd_queue(QUEUE_LCD, O_WRONLY, QUEUE_LCD_MAXMSG, QUEUE_LCD_MSGSIZE);
}

//void open_mqueues()
//{
//    Queue barcode_queue(QUEUE_BARCODE, O_RDONLY | O_NONBLOCK);
//    Queue keyboard_queue(QUEUE_KEYBOARD, O_RDONLY | O_NONBLOCK);
//    Queue card_reader_queue(QUEUE_CARDREADER, O_RDONLY | O_NONBLOCK)
//    Queue customer_display_queue(CUSTOMER_DISPLAY_QUEUE_NAME, O_WRONLY)
//    Queue receipt_queue(QUEUE_RECEIPT, O_WRONLY)
//}

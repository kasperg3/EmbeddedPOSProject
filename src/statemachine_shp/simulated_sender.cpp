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
    cout << "1" << endl;
    sleep(3);
    keyboard_queue.send("5");
    cout << "5" << endl;
    sleep(3);
    barcode_queue.send("5701115667007");
    cout << "5701115667007" << endl;
    sleep(3);
    keyboard_queue.send("<Enter>"); // go to pay
    cout << "<Enter>" << endl;
    sleep(3);
    keyboard_queue.send("1");
    cout << "1" << endl;
    sleep(3);
    card_reader_queue.send("123545");
    cout << "12345" << endl;
    sleep(3);
    numpad_queue.send("1");
    cout << "1" << endl;
    sleep(1);
    numpad_queue.send("2");
    cout << "2" << endl;
    sleep(1);
    numpad_queue.send("3");
    cout << "3" << endl;
    sleep(1);
    numpad_queue.send("4");
    cout << "4" << endl;
    sleep(3);
    keyboard_queue.send("<Enter>");
    cout << "<Enter>" << endl;

    return 0;
}



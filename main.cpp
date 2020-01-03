/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "src/peripherals/CardReader.hpp"
#include <sys/utsname.h>
#include "src/peripherals/GPIO.hpp"
#include "src/peripherals/NumpadDriver.hpp"
#include "src/peripherals/DisplayDriver.hpp"
#include <chrono>
#include "src/peripherals/InputEventDriver.h"
#include "src/database/db_interface.hpp"
#include "src/utilities/queue.h"
#include "src/peripherals/CustomerDisplay.hpp"


//Thread exercise
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>
#include <cstring>
#include <signal.h>
#include "src/Core.h"
#include "src/tasks/NumpadDriverTask.hpp"
#include "src/tasks/DisplayDriverTask.hpp"
#include "src/tasks/BarcodeScannerTask.hpp"
#include "src/tasks/CardReaderTask.hpp"
#include "src/tasks/ReceiptPrinterTask.hpp"
#include "src/tasks/KeyboardTask.h"
#include <sys/ioctl.h>
#include "src/tasks/CustomerDisplayTask.hpp"
#include "src/statemachine_shp/shpstatemachine.h"

void mqueuetest(){
    const int MAXMSG = 10;
    const int MSGSIZE = 1024;
    const char* queue_name = "/test_queue";

    Queue q(queue_name, 0, MAXMSG, MSGSIZE);
    Queue q2(queue_name, O_WRONLY);
    Queue q3(queue_name, O_RDONLY);

    for(int i = 0; i < 8; i++)
        q2.send("hellofellow" + std::to_string(i));

    for(int i = 0; i < 5; i++)
        std::cout << q3.receive() << std::endl;

    //q.flush();
    //q2.flush();
    q3.flush();

    if(q2.empty())
        std::cout << "The queue is empty" << std::endl;

}

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
    //displayDriver.clear();

    displayDriver.print(0,"c");
    displayDriver.print(66, "W");
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
            displayDriver.print(1,(char *)value);
            oldValue = value;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


int testPosix(){
    NumpadDriverTask numpadDriverTask;
    //numpadDriverTask.setMessageQueue("/message_queue");

    DisplayDriverTask displayDriverTask;
    //displayDriverTask.setMessageQueue("/message_queue");

    //The input
    NumpadDriver numpadDriver;
    DisplayDriver displayDriver;
    numpadDriver.init();
    displayDriver.init();
    displayDriver.clear();

    pthread_t numpadPublisher;
    pthread_t displayConsumer;

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&numpadPublisher, NULL, reinterpret_cast<void *(*)(void *)>(NumpadDriverTask::taskHandler), &numpadDriver);
    pthread_create(&displayConsumer, NULL, reinterpret_cast<void *(*)(void *)>(DisplayDriverTask::taskHandler), &displayDriver);

    pthread_join(numpadPublisher, NULL);
    pthread_join(displayConsumer, NULL);

}


void keyboardDriverTest(){
    // CardReader and scanner only works on Zybo
    const char *deviceName = "/dev/input/by-id/usb-USB_Adapter_USB_Device-event-kbd"; //Scanner
    //const char *deviceName = "/dev/input/by-id/usb-c216_0180-event-kbd";//Card Reader
    //const char *deviceName = "/dev/input/by-path/platform-i8042-serio-0-event-kbd"; //Keyboard
    InputEventDriver driver = InputEventDriver(deviceName);


    while(true){
        input_event inputEvent = driver.readEvent();
        //inputEvent.type == EV_KEY || inputEvent.type == EV_MSC
        if (inputEvent.type == EV_KEY)
            if(inputEvent.value == 1)
                printf("Value: %s \t Code: 0x%04x (%d) \t Type: %d \n", pressType[inputEvent.value], (int)inputEvent.code, (int)inputEvent.code, inputEvent.type);
        fflush(stdout);
    }
}
void receipt_and_database_test()
{
    DatabaseInterface dbi;
    Receipt receipt = dbi.createNewReceipt();
    SimpleItem snickers = dbi.getSimpleItemById(112);
    SimpleItem pepsi = dbi.getSimpleItemByName("Pepsi");
    receipt.addReceiptLine(snickers.getId(), snickers.getName(), snickers.getUnitPrice(), 2); //Add two snickers to receipt
    receipt.addReceiptLine(pepsi.getId(), pepsi.getName(), pepsi.getUnitPrice(), 2); //Add two pepsis

    receipt.setPaymentStatus("payed"); //When should you actually do this?
    dbi.completeTransaction(receipt);
    std::string receipt_string = receipt.stringifyReceipt();
    Queue receiptQ(QUEUE_RECEIPT,O_WRONLY,QUEUE_RECEIPT_MAXMSG,QUEUE_RECEIPT_MSGSIZE);
//    Queue receiptQ(QUEUE_RECEIPT, O_WRONLY);
    receiptQ.send(receipt_string);


}


void testBarcodeScannerTask(){

    BarcodeScannerTask barcodeScannerTask();
    pthread_t barcodePublisher;

    const char *deviceName = BARCODE_SCANNER_PATH; //Scanner
    InputEventDriver barcodeEventDriver(deviceName);

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&barcodePublisher, NULL, reinterpret_cast<void *(*)(void *)>(BarcodeScannerTask::taskHandler), &barcodeEventDriver);
    pthread_join(barcodePublisher, NULL);

}


void testCardReaderTask(){

    CardReaderTask cardReaderTask();
    pthread_t cardReaderPublisher;

    const char *deviceName = CARDREADER_PATH; //Card Reader
    InputEventDriver cardReaderEventDriver(deviceName);

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&cardReaderPublisher, NULL, reinterpret_cast<void *(*)(void *)>(CardReaderTask::taskHandler), &cardReaderEventDriver);
    pthread_join(cardReaderPublisher, NULL);

}

void testReceiptPrinterTask(){

    ReceiptPrinterTask receiptPrinterTask();
    pthread_t receiptConsumer;

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root (RPT).\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&receiptConsumer, NULL, reinterpret_cast<void *(*)(void *)>(ReceiptPrinterTask::taskHandler), NULL);
    pthread_join(receiptConsumer, NULL);

}

void testKeyboardTask(){

    KeyboardTask keyboardTask();
    pthread_t keyboardPublisher;

    const char *deviceName = KEYBOARD_PATH; //Card Reader
    InputEventDriver keyboardEventDriver(deviceName);

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }

    pthread_create(&keyboardPublisher, NULL, reinterpret_cast<void *(*)(void *)>(KeyboardTask::taskHandler), &keyboardEventDriver);
    pthread_join(keyboardPublisher, NULL);

}

void CustomerDisplayTest(){
    CustomerDisplayTask CD_task;
    CD_task.createQueue();

    CD_task.sendMessageToQ("Brain \n$10");
    sleep(2);
    CD_task.sendMessageToQ("YOLO \n$0500");
    sleep(2);
    CD_task.sendMessageToQ("Braincell \n$100");

    CustomerDisplay customerDisplay;
    pthread_t CDConsumer;
    pthread_create(&CDConsumer, NULL, reinterpret_cast<void *(*)(void *)>(CustomerDisplayTask::taskHandler), &customerDisplay);
    pthread_join(CDConsumer, NULL);

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

int main() {
    init_main();


    //---------------------- INSERT EXECUTION CODE HERE ----------------------//
    //receipt_and_database_test();
    //testReceiptPrinterTask();
    //mqueuetest();
    //ledTest();
    //numpadDriverTest();
    //displayDriverTest();
    //numpadToDisplayTest();
    //exercise1lec5();
    //theBomb();
    //testPosix();
    //keyboardDriverTest();
    //testBarcodeScannerTask();
    //testCardReaderTask();
    //testKeyboardTask();
    //CustomerDisplayTest();

    uid_t user_id = getuid();
    if(user_id > 0) {
        printf("Run as root.\n");
        exit(EXIT_FAILURE);
    }
    create_mqueues();

    CardReaderTask cardReaderTask();
    pthread_t cardReaderPublisher;
    const char *deviceName = CARDREADER_PATH; //Card Reader
    InputEventDriver cardReaderEventDriver(deviceName);
    pthread_create(&cardReaderPublisher, NULL, reinterpret_cast<void *(*)(void *)>(CardReaderTask::taskHandler), &cardReaderEventDriver);

    KeyboardTask keyboardTask();
    pthread_t keyboardPublisher;
    const char *deviceNameCR = KEYBOARD_PATH; //Card Reader
    InputEventDriver keyboardEventDriver(deviceNameCR);
    pthread_create(&keyboardPublisher, NULL, reinterpret_cast<void *(*)(void *)>(KeyboardTask::taskHandler), &keyboardEventDriver);

    BarcodeScannerTask barcodeScannerTask();
    pthread_t barcodePublisher;
    const char *deviceNameSC = BARCODE_SCANNER_PATH; //Scanner
    InputEventDriver barcodeEventDriver(deviceNameSC);
    pthread_create(&barcodePublisher, NULL, reinterpret_cast<void *(*)(void *)>(BarcodeScannerTask::taskHandler), &barcodeEventDriver);

    ReceiptPrinterTask receiptPrinterTask();
    pthread_t receiptConsumer;
    pthread_create(&receiptConsumer, NULL, reinterpret_cast<void *(*)(void *)>(ReceiptPrinterTask::taskHandler), NULL);

    ShpStateMachine sm;
    sm.run();

    return 0;
}

#include <iostream>
#include "db_interface.hpp"

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

using namespace std;


string state = "scan";

int main(int argc, char** argv)
{
    //Test completeTransaction():
    DatabaseInterface dbi;
    Receipt receipt = dbi.createNewReceipt();
    SimpleItem snickers = dbi.getSimpleItemById(112);
    SimpleItem pepsi = dbi.getSimpleItemByName("Pepsi");
    receipt.addReceiptLine(snickers.getId(), snickers.getName(), snickers.getUnitPrice(), 2); //Add two snickers to receipt
    receipt.addReceiptLine(pepsi.getId(), pepsi.getName(), pepsi.getUnitPrice(), 2); //Add two pepsis

    receipt.setPaymentStatus("payed"); //Needs to be done for database server to register the receipt and deduct items etc.
    dbi.completeTransaction(receipt);

    return 0;
}

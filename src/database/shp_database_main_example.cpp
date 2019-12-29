#include <iostream>
#include "db_interface.hpp"


using namespace std;

int main(int argc, char** argv)
{

    DatabaseInterface dbi;

//    [--Test getSimpleItemByIdentifier--]
//    dbi.getSimpleItemByBarcode("5000159461122");
//    SimpleItem snickers = dbi.getSimpleItemById(112);
//    SimpleItem pepsi = dbi.getSimpleItemByName("Pepsi");



//    [--Test getReceiptByNumber (22 is already in db)--]
//    Receipt receipt = dbi.getReceiptByNumber(22);


//    [--Test createNewReceipt --]
//    Receipt receipt = dbi.createNewReceipt();
//    cout << "Receipt number: " << receipt.getNumber() << endl;


    //Test completeTransaction():
    Receipt receipt = dbi.createNewReceipt();
    SimpleItem snickers = dbi.getSimpleItemById(112);
    SimpleItem pepsi = dbi.getSimpleItemByName("Pepsi");
    receipt.addReceiptLine(snickers.getId(), snickers.getName(), snickers.getUnitPrice(), 2); //Add two snickers to receipt
    receipt.addReceiptLine(pepsi.getId(), pepsi.getName(), pepsi.getUnitPrice(), 2); //Add two pepsis

    receipt.setPaymentStatus("payed"); //When should you actually do this?
    dbi.completeTransaction(receipt);

    return 0;
}

/*
 * database_interface.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: Catalin I. Ntemkas
 */
#include "db_interface.hpp"


using namespace std;

DatabaseInterface::DatabaseInterface() {
    _context = zmq::context_t (1);
    _socket = zmq::socket_t(_context, ZMQ_REQ);
    _socket.connect("tcp://localhost:5555");
}

DatabaseInterface::~DatabaseInterface()
{
}

DatabaseInterface::DatabaseInterface(ServerAddress ip, ServerPort port) {
    _context = zmq::context_t (1);
    _socket = zmq::socket_t(_context, ZMQ_REQ);
    _socket.connect("tcp://"+ip+":"+port);

}

std::string DatabaseInterface::sendRequest(std::string request)
{
    zmq::message_t reply;
    string msg_size = "msgsize/" + to_string(request.size());

    //Let the server know the size of our request:
    _socket.send(msg_size.data(), msg_size.size());

    //Server replies with ack if OK
    _socket.recv(&reply);
    string string_reply((const char*)reply.data(), reply.size());
    //cout << "Server replies: " << string_reply << endl;

    //Send actual request:
    _socket.send(request.data(), request.size());

    //Server responds with size of the data it will send
    _socket.recv(&reply);
    string string_response((const char*)reply.data(), reply.size());
    //cout << "Server replies: " << string_response << endl;

    //We acknowledge regardless of size (aggressive programming)
    _socket.send("ack", 3);

    //Receive the item data:
    _socket.recv(&reply);
    string item_data((const char*)reply.data(), reply.size());
    cout << "Server replies: " << item_data << endl;

    return item_data;

}


SimpleItem DatabaseInterface::getSimpleItemById(ItemId id) {

    return SimpleItem(getItemById(id));
}

SimpleItem DatabaseInterface::getSimpleItemByName(Name name) {
	return SimpleItem(getItemByName(name));
}

SimpleItem DatabaseInterface::getSimpleItemByBarcode(Barcode barcode) {
    return SimpleItem(getItemByBarcode(barcode));
}

Receipt DatabaseInterface::getReceiptByNumber(ReceiptNumber number)
{
    string receipt_data = sendRequest("get_receipt_by_num/" + to_string(number));
    cout << "receipt data: " << receipt_data << endl;
    istringstream data_stream(receipt_data);

    //receipt_data contains:
    //"#receipt_num:22#payment_status:payed
    //#receipt_line:*id;112*name;Snickers*price;10*quantity;1
    //#receipt_line:*id;125*name;Pepsi*price;15*quantity;1
    //#receipt_line:*id;152*name;BKI Kaffen Alle Kali*price;45*quantity;1"

    vector<string> tokens;
    string token;
    Receipt receipt(number);
    while(getline(data_stream, token, '#'))
        tokens.push_back(token);

    for(string t : tokens)
    {
        int pos = t.find(":");
        string key = t.substr(0, pos);  //Left side of ':' becomes key
        string val = t.substr(pos + 1); //Right side becomes value. Like in python dict

        if(key == "payment_status")
            receipt.setPaymentStatus(val);
        else if(key == "receipt_line")
        {
            ReceiptLine line = createReceiptLineFromVal(val);
            receipt.addReceiptLine(line);
        }
    }

    return receipt;
}

Item DatabaseInterface::getItemById(ItemId id) {
    string item_data = sendRequest("get_item_by_id/" + to_string(id));
    return createItemFromItemData(item_data);}

Item DatabaseInterface::getItemByName(Name name)
{
    string item_data = sendRequest("get_item_by_name/" + name);
    return createItemFromItemData(item_data);
}

Item DatabaseInterface::getItemByBarcode(Barcode barcode)
{
    string item_data = sendRequest("get_item_by_barcode/" + barcode);

    Item item = createItemFromItemData(item_data);
//    cout << "\n-----------\n";
//    cout << "Item name: " << item.getName() << endl;
//    cout << "unit price: " << item.getUnitPrice() << endl;
//    cout << "cost price: " << item.getCostPrice() << endl;

//    vector<BulkPrice> bps = item.getBulkPrices();
//    for(auto bp: bps)
//    {
//        cout << "bulk price: " << bp.bulk_price << endl;
//        cout << "quantity: " << bp.quantity << endl;
//    }

//    vector<Barcode> bcs = item.getBarcodes();
//    for(auto bc : bcs)
//        cout << bc << endl;

    return item;
}

Receipt DatabaseInterface::createNewReceipt()
{

    string receipt_data = sendRequest("create_new_receipt"); //This simply returns the id of the receipt.
                                                             //Id increments every time this function is called.

    return Receipt(stoi(receipt_data));
}

void DatabaseInterface::completeTransaction(Receipt receipt)
{
    //Requesting: complete_transaction/#receipt_num:22#payment_status:payed
    //#receipt_line:*id;112*name;Snickers*price;10*quantity;1
    //#receipt_line:*id;125*name;Pepsi*price;15*quantity;1
    //#receipt_line:*id;152*name;BKI Kaffen Alle Kali*price;45*quantity;1

    string request = "complete_transaction/";
    request += "#receipt_num:"+to_string(receipt.getNumber());
    request += "#payment_status:" + receipt.getPaymentStatus();

    for(auto line: receipt.getReceiptLines())
    {
        request += "#receipt_line:*id;" + to_string(line.id);
        request += "*name;" + line.name;
        request += "*price;" + to_string(line.price);
        request += "*quantity;" + to_string(line.quantity);
    }

    cout << "Will send to db_interface ------------" << endl;
    cout << request << endl;

    string data = sendRequest(request);
    cout << "Server answered: " << data << endl;

}

PaymentStatus DatabaseInterface::getPaymentStatusPayed() {
	return DB_RECEIPT_PAYED;
}

PaymentStatus DatabaseInterface::getPaymentStatusCancelled() {
	return DB_RECEIPT_CANCELLED;
}

//Helper functions

Item DatabaseInterface::createItemFromItemData(string item_data)
{
    istringstream data_stream(item_data);
    string token;
    vector<string> tokens;
    Item item;
    while(getline(data_stream, token, '#'))
        tokens.push_back(token);

    for(string t : tokens)
    {
        int pos = t.find(":");
        string key = t.substr(0, pos);  //Left side of ':' becomes key
        string val = t.substr(pos + 1); //Right side becomes value. Like in python dict

        if(key == "id")
            item.setId(stoi(val));
        else if(key == "name")
            item.setName(val);
        else if(key == "uprice")
            item.setUnitPrice(stod(val));
        else if(key == "cprice")
            item.setCostPrice(stod(val));
        else if(key == "stock")
            item.setStock(stoi(val));
        else if(key == "barcode")
            item.addBarcode(val);
        else if(key == "bulkp")
        {
            BulkPrice bulkprice = createBulkPriceFromVal(val);
            item.addBulkPrice( bulkprice );
        }
    }
    return item;
}

BulkPrice DatabaseInterface::createBulkPriceFromVal(string val)
{
    // val contains "*quantity;5*price;8"
    int first_semicolon_pos     = val.find(';');
    int second_asterisk_pos     = val.find('*', first_semicolon_pos + 1);
    int second_semicolon_pos    = val.find(';', second_asterisk_pos + 1);

    string quantity(val.begin() + first_semicolon_pos + 1, val.begin() + second_asterisk_pos ); //Make a substring. This way looks less
    string price(val.begin() + second_semicolon_pos + 1, val.end());                            //convoluted than actually using substr function

    return BulkPrice(stod(quantity), stod(price));
}

ReceiptLine DatabaseInterface::createReceiptLineFromVal(string val)
{
    //val contains "*id;112*name;Snickers*price;10*quantity;1"
    int first_semicolon = val.find(';');
    int second_semicolon = val.find(';', first_semicolon + 1);
    int third_semicolon = val.find(';', second_semicolon + 1);
    int fourth_semicolon = val.find(';', third_semicolon + 1);

    int first_asterisk = val.find('*');
    int second_asterisk = val.find('*', first_asterisk + 1);
    int third_asterisk = val.find('*', second_asterisk + 1);
    int fourth_asterisk = val.find('*', third_asterisk + 1);

    string id(val.begin() + first_semicolon + 1, val.begin() + second_asterisk);
    string name(val.begin() + second_semicolon + 1, val.begin() + third_asterisk);
    string price(val.begin() + third_semicolon + 1, val.begin() + fourth_asterisk);
    string quantity(val.begin() + fourth_semicolon + 1, val.end());

    return ReceiptLine(stoi(id), name, stoi(quantity), stoi(price));

}


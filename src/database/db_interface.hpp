/*
 * database_interface.hpp
 *
 *  Created on: Nov 2, 2017
 *      Author: Catalin I. Ntemkas
 */

#ifndef DB_INTERFACE_HPP_

#define DB_INTERFACE_HPP_

#include <zmq.hpp> //Changed from .h to .hpp for cpp bindings
#include <assert.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "db_interface_constants.hpp"
#include "item.hpp"
#include "simple_item.hpp"
#include "receipt.hpp"

typedef std::string ServerAddress;
typedef std::string ServerPort;

class DatabaseInterface {
public:
	DatabaseInterface();
	DatabaseInterface(ServerAddress, ServerPort);
	virtual ~DatabaseInterface();

	SimpleItem getSimpleItemById(ItemId);
	SimpleItem getSimpleItemByName(Name);
	SimpleItem getSimpleItemByBarcode(Barcode);
	Receipt getReceiptByNumber(ReceiptNumber);
	
	PaymentStatus getPaymentStatusPayed();
	PaymentStatus getPaymentStatusCancelled();

	Receipt createNewReceipt();
	void completeTransaction(Receipt);

private:    
    zmq::context_t _context;
    zmq::socket_t _socket;

	Item getItemById(ItemId);
	Item getItemByName(Name);
	Item getItemByBarcode(Barcode);

	std::string sendRequest(std::string request);

    Item createItemFromItemData(std::string item_data);
    BulkPrice createBulkPriceFromVal(std::string val);
    ReceiptLine createReceiptLineFromVal(std::string val);
};
#endif /* DB_INTERFACE_HPP_ */



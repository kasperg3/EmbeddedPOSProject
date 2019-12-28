/*
 * item.hpp
 *
 *  Created on: Jan 10, 2018
 *      Author: Catalin I. Ntemkas
 */

#ifndef SIMPLE_ITEM_HPP_
#define SIMPLE_ITEM_HPP_

#include <string>
#include <vector>
#include "item.hpp"

class SimpleItem {
private:
	Item item;

public:
	SimpleItem();
	SimpleItem(Item item);
	virtual ~SimpleItem();

	ItemId getId();
	Name getName();
	Stock getStock();
	UnitPrice getUnitPrice();
	std::vector<BulkPrice> getBulkPrices();
	std::vector<Barcode> getBarcodes();
};

#endif /* ITEM_HPP_ */

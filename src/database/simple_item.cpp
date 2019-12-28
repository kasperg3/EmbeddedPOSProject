/*
 * item.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: Catalin I. Ntemkas
 */

#include "simple_item.hpp"

SimpleItem::SimpleItem() {
	// TODO Auto-generated constructor stub

}

SimpleItem::SimpleItem(Item item) {
	// TODO Auto-generated constructor stub
	this->item = item;
}

SimpleItem::~SimpleItem() {
	// TODO Auto-generated destructor stub
}

ItemId SimpleItem::getId() {
	return item.getId();
}

Name SimpleItem::getName() {
	return item.getName();
}

UnitPrice SimpleItem::getUnitPrice() {
	return item.getUnitPrice();
}

Stock SimpleItem::getStock() {
	return item.getStock();
}

std::vector<Barcode> SimpleItem::getBarcodes() {
	return item.getBarcodes();
}

std::vector<BulkPrice> SimpleItem::getBulkPrices() {
	return item.getBulkPrices();
}


/*
 * item.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: Catalin I. Ntemkas
 */

#include "item.hpp"

Item::Item() {
	// TODO Auto-generated constructor stub

}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

void Item::setId(ItemId id) {
	this->id = id;
}

void Item::setName(Name name) {
	this->name = name;
}

void Item::setUnitPrice(UnitPrice unit_price) {
	this->unit_price = unit_price;
}

void Item::setCostPrice(CostPrice cost_price) {
	this->cost_price = cost_price;
}

void Item::setStock(Stock stock) {
	this->stock = stock;
}

ItemId Item::getId() {
	return id;
}

Name Item::getName() {
	return name;
}

UnitPrice Item::getUnitPrice() {
	return unit_price;
}

CostPrice Item::getCostPrice() {
	return cost_price;
}

Stock Item::getStock() {
	return stock;
}

std::vector<Barcode> Item::getBarcodes() {
	return barcodes;
}

std::vector<BulkPrice> Item::getBulkPrices() {
	return bulk_prices;
}

void Item::addBulkPrice(Quantity quantity, Price price) {
	bulk_prices.push_back( BulkPrice(quantity, price) );
}

void Item::addBulkPrice(BulkPrice bulk_price) {
	bulk_prices.push_back(bulk_price);
}

void Item::addBarcode(Barcode barcode) {
	barcodes.push_back(barcode);
}

void Item::removeBulkPrice(Position pos) {
	bulk_prices.erase(bulk_prices.begin() + pos);
}

void Item::removeBarcode(Position pos) {
	barcodes.erase(barcodes.begin() + pos);
}

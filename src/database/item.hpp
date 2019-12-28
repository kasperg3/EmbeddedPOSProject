/*
 * item.hpp
 *
 *  Created on: Jan 10, 2018
 *      Author: Catalin I. Ntemkas
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <vector>

typedef int ItemId;
typedef float Price;
typedef Price UnitPrice;
typedef Price CostPrice;
typedef int Quantity;
typedef int Stock;
typedef std::string Name;
typedef std::string Barcode;
typedef int Position;

typedef struct BulkPrice {
	Quantity quantity;
	Price bulk_price;
	BulkPrice(Quantity q, Price p) : quantity(q), bulk_price(p){}
} BulkPrice;

class Item {
private:
	ItemId id = 0;
	Name name;
	Stock stock = 0;
	UnitPrice unit_price = 0;
	CostPrice cost_price = 0;
	std::vector<BulkPrice> bulk_prices;
	std::vector<Barcode> barcodes;

public:
	Item();
	virtual ~Item();

	void setId(ItemId);
	void setName(Name);
	void setStock(Stock);
	void setUnitPrice(UnitPrice);
	void setCostPrice(CostPrice);

	ItemId getId();
	Name getName();
	Stock getStock();
	UnitPrice getUnitPrice();
	CostPrice getCostPrice();
	std::vector<BulkPrice> getBulkPrices();
	std::vector<Barcode> getBarcodes();

	void addBulkPrice(Quantity, Price);
	void addBulkPrice(BulkPrice);
	void addBarcode(Barcode);

	void removeBulkPrice(Position);
	void removeBarcode(Position);

};

#endif /* ITEM_HPP_ */

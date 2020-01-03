/*
 * receipt.hpp
 *
 *  Created on: Jan 8, 2018
 *      Author: Catalin I. Ntemkas
 */

#ifndef RECEIPT_HPP_
#define RECEIPT_HPP_

#include "item.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iomanip>      // std::setprecision
#include <sstream>

typedef long int ReceiptNumber;
typedef std::string PaymentStatus;
typedef float Amount;
typedef float LineAmount;

typedef struct ReceiptLine {
	ItemId id;
	Name name;
	Quantity quantity;
	Price price;
	LineAmount total_price;
	ReceiptLine(ItemId i, Name n, Quantity q, Price p) : id(i), name(n), quantity(q), price(p) {
		total_price = q*p;
	}
} ReceiptLine;

class Receipt {
private:
	ReceiptNumber number = 0;
	PaymentStatus payment_status = "";
	Amount amount = 0;
	std::vector<ReceiptLine> lines;

public:
	Receipt();
	Receipt(ReceiptNumber);
	virtual ~Receipt();

	ReceiptNumber getNumber();
	PaymentStatus getPaymentStatus();
	Amount getAmount();
	std::vector<ReceiptLine> getReceiptLines();

	void setPaymentStatus(PaymentStatus);

	void addReceiptLine(ItemId, Price, Quantity);
	void addReceiptLine(ItemId, Name, Price, Quantity);
	void addReceiptLine(ReceiptLine);
	void removeReceiptLine(Position);
    std::string stringifyLine(ReceiptLine line);
    std::string stringifyReceipt();

    std::string stringifyLineToDisplay(ReceiptLine line);
};

#endif /* RECEIPT_HPP_ */

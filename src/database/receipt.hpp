/*
 * receipt.hpp
 *
 *  Created on: Jan 8, 2018
 *      Author: Catalin I. Ntemkas
 */

#ifndef RECEIPT_HPP_
#define RECEIPT_HPP_

#include "item.hpp"

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
};

#endif /* RECEIPT_HPP_ */

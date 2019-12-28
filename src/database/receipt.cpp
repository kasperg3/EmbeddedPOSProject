/*
 * receipt.cpp
 *
 *  Created on: Jan 8, 2018
 *      Author: Catalin I. Ntemkas
 */

#include "receipt.hpp"

Receipt::Receipt() {
	// TODO Auto-generated constructor stub
}

Receipt::Receipt(ReceiptNumber num) {
	number = num;
}

Receipt::~Receipt() {
	// TODO Auto-generated destructor stub
}

ReceiptNumber Receipt::getNumber() {
	return number;
}

PaymentStatus Receipt::getPaymentStatus() {
	return payment_status;
}

Amount Receipt::getAmount() {
	return amount;
}

std::vector<ReceiptLine> Receipt::getReceiptLines() {
	return lines;
}

void Receipt::setPaymentStatus(PaymentStatus status) {
	payment_status = status;
}

void Receipt::addReceiptLine(ItemId id, UnitPrice price, Quantity quantity){
    addReceiptLine(ReceiptLine(id, "", quantity, price)); // <-- Bug from Catalin. price and quantity arguments are swapped wrt. constructor
}

void Receipt::addReceiptLine(ItemId id, Name name, UnitPrice price, Quantity quantity){
//	addReceiptLine(ReceiptLine(id, name, price, quantity)); // <-- Bug from Catalin. price and quantity arguments are swapped wrt. constructor
    addReceiptLine(ReceiptLine(id, name, quantity, price));
}

void Receipt::addReceiptLine(ReceiptLine line) {
    lines.push_back(line);
    amount += line.total_price;
}

void Receipt::removeReceiptLine(Position pos) {
    amount -= lines.at(pos).total_price;
    lines.erase(lines.begin() + pos);
}

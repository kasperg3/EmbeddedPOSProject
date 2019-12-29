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

std::string Receipt::stringifyLine(ReceiptLine line) {
    std::stringstream stream;
    Price price = line.price;
    stream << std::fixed << std::setprecision(2) << price;
    std::string s = stream.str();

    Name name = line.name;
    Quantity quantity = line.quantity;
    Price totalPrice = line.total_price;
    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << totalPrice;
    std::string s2 = stream2.str();

    std::string out_line = name +" x"+std::to_string(quantity)+" $"+ s+ + "\n itemtotal: " + "$"+s2+"\n";
   // std::cout << "outline:\n" << out_line << std::endl;
    return out_line;
}

std::string Receipt::stringifyReceipt() {
    std::string output;

    float total = 0.0;
    std::string total_string;
    output = "\t  ESD shop\nBest Deals Anywhere\n\n";
    for(int i = 0; i < lines.size(); i++)
    {
        output.append(stringifyLine(lines[i]));
        total += lines[i].total_price;
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << total;
    std::string s = stream.str();

    total_string = "\nTotal: $" + s;
    output.append(total_string);
    output.append("\nServiced by: NLO\n");

    std::cout << "test output\n\n" <<  output << std::endl << std::endl;
    return output;
}

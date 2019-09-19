//
// Created by kasper on 9/19/19.
//

#include "../header/CardReader.h"
//invalid card: 4321543265437654
CardReader::CardReader() {
}

bool CardReader::luhnAlgorithm() {
    int nDigits = 16;
    int parity = nDigits%2;
    int sum = 0;
    for(int i = 0; i < nDigits; i++){
        int digit = (int)cardNumber[i]-'0';
        if(i % 2 == parity)
            digit = digit*2;
        if(digit > 9)
            digit = digit - 9;
        sum += digit;
    }

    int result = ((sum % 10) == parity);

    //std::cout  << std::endl << "account number: " << cardNumber << std::endl;
    //std::cout << "sum: " << sum << std::endl;

    return result;
}

int CardReader::waitForSwipe() {

    std::string line;
    std::string fileName = "/home/kasper/CLionProjects/embeddedProj/swipe";
    std::ifstream inFile(fileName.c_str());
    if (!inFile) {
        //std::cout << "Unable to open file: " << fileName;
        return 1;
    }else{
        //std::cout << "Succesfully opened file: " << fileName << std::endl;
    }

    while ( getline(inFile, line)) {
        cardNumber = line;
        return 0;
    }
}

void CardReader::setCardNumber(std::string numberString) {
    cardNumber = numberString;
}

std::string CardReader::getCardNumber() {
    return cardNumber;
}

//
// Created by kasper on 9/19/19.
//

#include "CardReader.hpp"

//invalid card: 4321543265437654
CardReader::CardReader() {
}

bool CardReader::luhnAlgorithm() {
    int nDigits = 16;
    int parity = nDigits % 2;
    int sum = 0;
    for (int i = 0; i < nDigits; i++) {
        int digit = (int) cardNumber[i] - '0';
        if (i % 2 == parity)
            digit = digit * 2;
        if (digit > 9)
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
    std::string fileName = "/dev/swipe";
    std::ifstream inFile(fileName.c_str());
    if (!inFile) {
        return 1;
    }
    while (getline(inFile, line)) {
        cardNumber = line;
        inFile.close();
        return 0;
    }
}

CardReader::~CardReader(){
}

int CardReader::runCardReader() {
    currentState = ST_IDLE;
    //Switch Case: MOVE THIS TO ANOTHER CLASS WHEN EXPANDING
    while (currentState != ST_STOP) {
        switch (currentState) {
            case ST_IDLE: {
                currentState = ST_WAITFORSWIPE;
                break;
            }
            case ST_FAILURE: {
                std::cout << "Failed to validate card" << std::endl;
                currentState = ST_IDLE;
                break;
            }
            case ST_WAITFORSWIPE: {
                std::cout << "Please swipe card" << std::endl;
                CardReader cardReader;
                cardReader.waitForSwipe();
                if (!cardReader.luhnAlgorithm()) {
                    currentState = ST_FAILURE;
                }else
                    currentState = ST_INPUTPIN;
                break;
            }
            case ST_INPUTPIN: {
                std::string pinCode;
                std::cout << "Please enter pin: ";
                std::cin >> pinCode;
                if (pinCode.length() == 4)
                    currentState = ST_APPROVEAMOUNT;
                else
                    std::cout << "Invalid pin. ";
                break;
            }
            case ST_APPROVEAMOUNT: {
                std::cout << "Order total = 69.69 DKK, press 'a' to approve: ";
                char input;
                std::cin >> input;
                if (input == 'a') {
                    std::cout << "Transaction approved,thank you for the purchase." << std::endl;
                    currentState = ST_STOP;
                } else {
                    std::cout << "Transaction terminated, input recieved: " << input << std::endl;
                    currentState = ST_IDLE;
                }
                break;
            }
            case ST_STOP: {
                currentState = ST_STOP;
                return 0;
            }
        }
    }

}

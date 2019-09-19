/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

bool luhnAlgorithm(std::string line){
    int nDigits = 16;
    int parity = nDigits%2;
    int sum = 0;
    for(int i = 0; i < nDigits; i++){
        int digit = (int)line[i]-'0';
        if(i % 2 == parity)
            digit = digit*2;
        if(digit > 9)
            digit = digit - 9;
        sum += digit;
    }

    int result = ((sum % 10) == parity);

    //std::cout  << std::endl << "account number: " << line << std::endl;
    //std::cout << "sum: " << sum << std::endl;

    return result;
}


int main() {
    std::string line;
    std::string fileName = "/dev/swipe";
    std::ifstream inFile(fileName.c_str());
    if (!inFile) {
        std::cout << "Unable to open file: " << fileName;
        return 1;
    }else{
        std::cout << "Succesfully opened file: " << fileName << std::endl;
    }
    while ( getline(inFile, line)) {
        std::cout << "result: " << luhnAlgorithm(line) << std::endl;
    }
}

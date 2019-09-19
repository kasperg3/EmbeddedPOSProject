#include <iostream>
#include <iomanip>
#include <fstream>

int main() {
    int sum = 0;
    int x;
    std::string line;
    std::ifstream inFile;
    std::string fileName = "/dev/swipe";
    inFile.open(fileName);
    if (!inFile) {
        std::cout << "Unable to open file: " << fileName;
        exit(1); // terminate with error
    }else{
        std::cout << "Succesfully opened file: " << fileName;
    }

    int nDigits = 16;
    int parity = nDigits%2;
    while(true){
        int sum = 0;
        while (getline(inFile, line)) {
            if(line.length() != 16){
                for(int i = 0; i < line.length()-1; i++){
                    int digit = (int)line[i]-48;
                    if(digit % 2 )
                        digit = digit*2;
                    if(digit > 9)
                        digit = digit - 9;
                    sum += digit;
                }

                bool result = ((sum % 10) == 0);

                std::cout << "account number: " << line << std::endl;
                std::cout << "sum: " << sum << std::endl;
                std::cout << "Result:  " << result;
            }else{
                std::cout << "Incorrect amount of digits in cardnumber" << std::endl;
            }
        }
    }



    inFile.close();
    std::cout << "Sum = " << sum << std::endl;
    return 0;
}
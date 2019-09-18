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
    while(true){
        while (getline(inFile, line)) {
            if(line.length() != 16){
                for(int i = 0; i < line.length(); i++){
                    if(i % 2 == 1){
                        if(((int)line[i]-48) * 2 > 9){ sum += ((int)line[i]-48) * 2 - 9;}
                    }else{
                        sum += ((int)line[i]-48);
                    }
                }
                if(sum%10){
                    std::cout << "Correct checksum" << std::endl;
                }else{
                    std::cout << "Incorrect checksum" << std::endl;

                }
            }else{
                std::cout << "Incorrect amount of digits in cardnumber" << std::endl;
            }
        }
    }


    inFile.close();
    std::cout << "Sum = " << sum << std::endl;
    return 0;
}
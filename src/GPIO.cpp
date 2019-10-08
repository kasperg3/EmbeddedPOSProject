//
// Created by kasper on 10/4/19.
// BASED OF LEON'S CODE example.cpp FROM LAB 3
//

#include "../include/GPIO.h"

#include <utility>


GPIO::GPIO() {}

GPIO::GPIO(std::string pinString) : pin_number(std::move(pinString)) {}

int GPIO::writeToFile(std::string write_pin_path, std::string value){

    // Open file
    std::ofstream write_file( write_pin_path.c_str() );
    if(!write_file.is_open())
    {
        std::cerr << "Unable to open " << write_pin_path << std::endl;
        return -1;
    }

    // Write value
    write_file << value;
}

int GPIO::readFromFile(std::string file, std::string &outputString) {
    std::string line;
    std::ifstream inFile(file.c_str());
    if (!inFile) {
        return 1;
    }
    while (getline(inFile, line)) {
        outputString = line;
        return 0;
    }
}


int GPIO::setPinNumber(int number) {
    this->pin_number = std::to_string(number);
}

int GPIO::exportPin() {
    if(pin_number.length() <= 0){
        std::cerr << "Not a valid pin_number" << std::endl;
    }
    // Define path
    std::string export_path = "/sys/class/gpio/export";
    // Open file
    std::ofstream export_file( export_path.c_str() );

    // Check if the file was actually opened
    if(!export_file.is_open())
    {
        std::cerr << "Unable to open " << export_path << std::endl;
        return -1;
    }
    // Write pin numbers to file
    export_file << pin_number << std::endl;

    // Close the file
    export_file.close();

}

int GPIO::unexportPin() {
    if(pin_number.length() <= 0){
        std::cerr << "Not a valid pin_number" << std::endl;
    }
    // Define path
    std::string export_path = "/sys/class/gpio/export";
    // Open file
    std::ofstream export_file( export_path.c_str() );

    // Check if the file was actually opened
    if(!export_file.is_open())
    {
        std::cerr << "Unable to open " << export_path << std::endl;
        return -1;
    }
    // Write pin numbers to file
    export_file << pin_number << std::endl;

    // Close the file
    export_file.close();
    return 0;
}

int GPIO::setPinDirection(std::string direction) {

    // Define paths
    std::string pin_path = "/sys/class/gpio/gpio" + pin_number + "/direction";

    // Open files
    std::ofstream pin_file( pin_path.c_str() );
    if(!pin_file.is_open()){
        std::cerr << "Unable to open " << pin_path << std::endl;
        return -1;
    }

    // Write directions to the files
    pin_file << direction;

    // Close the files
    pin_file.close();

    return 0;
}

int GPIO::setPinValue(std::string pinValue) {
    if(std::stoi(pinValue) == 1 or std::stoi(pinValue) == 0){
        // Define path
        std::string write_pin_path = "/sys/class/gpio/gpio" + pin_number + "/value";

        // Open file
        std::ofstream write_pin_file( write_pin_path.c_str() );
        if(!write_pin_file.is_open())
        {
            std::cerr << "Unable to open " << write_pin_path << std::endl;
            return -1;
        }

        // Write value
        write_pin_file << pinValue;
        return 0;
    }else{
        std::cerr << "Not a valid pin value " << std::endl;
    }
}

int GPIO::getPinValue(std::string &string_out) {
    // Define path
    std::string read_path = "/sys/class/gpio/gpio" + pin_number + "/value";

    // Open file
    std::ifstream read_file( read_path.c_str() );
    if(!read_file.is_open())
    {
        std::cerr << "Unable to open " << read_path << std::endl;
        return -1;
    }

    // read value
    read_file >> string_out;
    return 0;
}

void GPIO::set(void) {
    setPinValue("1");
}

void GPIO::clear(void) {
    setPinValue("0");
}

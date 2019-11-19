//
// Created by kasper on 10/4/19.
// BASED OF LEON'S CODE example.cpp FROM LAB 3
//

#include "GPIO.hpp"

#include <utility>


GPIO::GPIO() {}

GPIO::GPIO(std::string pinString) {
    pin_number = pinString;
}

int GPIO::writeToFile(std::string write_pin_path, std::string value){

    // Open file
    std::ofstream write_file( write_pin_path.c_str() );
    if(!write_file.is_open()){
        std::cerr << "Unable to open " << write_pin_path << std::endl;
        exit (EXIT_FAILURE);
    }

    // Write value
    write_file << value;
    write_file.close();
    return 0;
}

int GPIO::readFromFile(std::string file, std::string &outputString) {
    // Open file
    std::ifstream read_file( file.c_str() );
    if(!read_file){
        std::cerr << "Unable to open " << file << std::endl;
        exit (EXIT_FAILURE);
    }

    // read value
    read_file >> outputString;
    read_file.close();
    return 0;
}


int GPIO::setPinNumber(int number) {
    this->pin_number = std::to_string(number);
    return 0;
}

int GPIO::exportPin() {
    if(pin_number.length() <= 0){
        std::cerr << "Not a valid pin_number" << std::endl;
        exit (EXIT_FAILURE);
    }
    // Define path
    std::string export_path = "/sys/class/gpio/export";
    // Open file
    writeToFile(export_path,pin_number);
    return 0;
}

int GPIO::unexportPin() {
    if(pin_number.length() <= 0){
        std::cerr << "Not a valid pin_number" << std::endl;
        exit (EXIT_FAILURE);
    }
    // Define path
    std::string export_path = "/sys/class/gpio/export";
    // Open file
    writeToFile(export_path, pin_number);
    return 0;
}

int GPIO::setPinDirection(std::string direction) {
    // Define paths
    std::string pin_path = "/sys/class/gpio/gpio" + pin_number + "/direction";
    return writeToFile(pin_path, direction);
}

int GPIO::setPinValue(std::string pinValue) {
    if(std::stoi(pinValue) == 1 or std::stoi(pinValue) == 0){
        // Define path
        std::string write_pin_path = "/sys/class/gpio/gpio" + pin_number + "/value";
        // Open file
        return writeToFile(write_pin_path, pinValue);
    }else{
        std::cerr << "Not a valid pin value " << std::endl;
    }
}

int GPIO::getPinValue(std::string &string_out) {
    // Define path
    std::string read_path = "/sys/class/gpio/gpio" + pin_number + "/value";
    return readFromFile(read_path, string_out);
}

void GPIO::set(void) {
    setPinValue("1");
}

void GPIO::clear(void) {
    setPinValue("0");
}

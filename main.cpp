/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "include/CardReader.h"


enum States
{
    ST_IDLE,
    ST_FAILURE,
    ST_WAITFORSWIPE,
    ST_APPROVEAMOUNT,
    ST_INPUTPIN,
    ST_STOP
};

States currentState = ST_IDLE;

int main() {

    //Switch Case: MOVE THIS TO ANOTHER CLASS WHEN EXPANDING
    while(currentState != ST_STOP){
        switch (currentState) {
            case ST_IDLE:{
                currentState = ST_WAITFORSWIPE;
                break;
            }
            case ST_FAILURE:{
                std::cout << "Failed to validate card" << std::endl;
                currentState = ST_IDLE;
                break;
            }
            case ST_WAITFORSWIPE:{
                std::cout << "Please swipe card" << std::endl;
                CardReader cardReader;
                cardReader.waitForSwipe();
                if( !cardReader.luhnAlgorithm() ){ currentState = ST_FAILURE; break;}
                currentState = ST_INPUTPIN;
                break;
            }
            case ST_INPUTPIN:{
                std::string pinCode;
                std::cout << "Please enter pin: "; std::cin >> pinCode;
                if(pinCode.length() == 4)
                    currentState = ST_APPROVEAMOUNT;
                else
                    std::cout << "Invalid pin. ";
                break;
            }
            case ST_APPROVEAMOUNT:{
                std::cout << "Order total = 49.99 DKK, press 'a' to approve: ";
                char input;
                std::cin >> input;
                if(input == 'a'){
                    std::cout << "Transaction approved,thank you for the purchase." << std::endl;
                    currentState = ST_STOP;
                }else{
                    std::cout << "Transaction terminated, input recieved: " << input << std::endl;
                    currentState = ST_IDLE;
                }
            break;
            }
            case ST_STOP:{
                break;
            }
        }
    }
}

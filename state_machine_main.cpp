/*
 * Made By: Kasper Andreas Grøntved
 * Course: embedded software development
 * */

#include <iostream>
#include "src/state_handling/StateMachine.h"

int main()
{
    StateMachine stateMachine = StateMachine();
    stateMachine.init();
    stateMachine.start();

    return 0;
}

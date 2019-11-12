/*
 * BombStateMachine.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: leon
 */

#include "BombStateMachine.hpp"

BombStateMachine::BombStateMachine()
{
	state = SETTING;
	timer = 5;
}

BombStateMachine::~BombStateMachine()
{

}

void BombStateMachine::init(void)
{
	inputs.push_back( new PushButton("988", "UP", &events) );
	inputs.push_back( new PushButton("989", "DOWN", &events) );
	inputs.push_back( new PushButton("990", "ARM", &events) );
	inputs.push_back( new Timer(UPDATE_PERIOD,1000000, "TICK", &events) );
}

void BombStateMachine::checkInputs(void)
{
	for (auto event_handler : inputs)
		event_handler->checkForEvents();
}

void BombStateMachine::start(void)
{
	while(true)
	{
		checkInputs();
		updateState();

		if(state == EXIT)
			return;

		usleep(UPDATE_PERIOD);
	}
}

void BombStateMachine::printEvents(void)
{
	if (! events.isEmpty() )
	{
		std::string event;
		events.popEvent(event);
		std::cout << event << std::endl;
	}
}

void BombStateMachine::updateState(void)
{
	if (! events.isEmpty() )
	{
		std::string event;
		events.popEvent(event);

		switch(state)
		{
		case SETTING:
			std::cout << event << std::endl;

			if(event == "UP" && timer < 10){
                timer++;
                std::cout << "timer = " << timer << std::endl;
            }else if(event == "DOWN" && timer > 1){
                timer--;
                std::cout << "timer = " << timer << std::endl;
            }else if(event == "ARM"){
                state = TIMING;
            }
            break;

        case TIMING:
            if(event == "TICK" && timer > 0){
                timer--;
                std::cout << timer << std::endl;
            }
            if(timer == 0){
                std::cout << "BOOM" << std::endl;
                state = EXIT;
            }
            if(event == "UP" ){
                code.append("1");
            }else if(event == "DOWN"){
                code.append("0");
            }else if(event == "ARM"){
                if(code == defuseCode){
                    std::cout << "DEFUSED THE BOMB" << std::endl;
                    code = "";
                    state = SETTING;
                }else{
                    std::cout << "Wrong code, try again" << std::endl;
                    code = "";
                }
            }
            break;
        default:
			state = SETTING;
		}
	}
}

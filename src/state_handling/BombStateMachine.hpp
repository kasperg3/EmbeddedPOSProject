//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef STATE_HANDLING_BOMBSTATEMACHINE_HPP_
#define STATE_HANDLING_BOMBSTATEMACHINE_HPP_

#define UPDATE_PERIOD 20000 // [μs]

#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../peripherals/PushButton.hpp"
#include "../peripherals/Timer.hpp"
#include "../event_handling/EventQueue.hpp"



class BombStateMachine {

private:
	enum state_t : int {SETTING, TIMING, EXIT};
	state_t state;

	int timer;
	std::string code = "" ;
    std::string defuseCode = "11011";
	EventQueue events;
	std::vector<EventHandler*> inputs;

public:
	BombStateMachine();
	virtual ~BombStateMachine();

	void init(void);
	void start(void);
	void checkInputs(void);
	void updateState(void);
	void printEvents(void);

};

#endif /* STATE_HANDLING_BOMBSTATEMACHINE_HPP_ */

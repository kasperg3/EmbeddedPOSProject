//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef PERIPHERALS_PUSHBUTTON_HPP_
#define PERIPHERALS_PUSHBUTTON_HPP_

#include <string>
#include <iostream>
#include "GPIO.hpp"
#include "../event_handling/EventHandler.hpp"

class PushButton : public EventHandler
{
private:
	GPIO gpio;

	std::string current_input, previous_input, current_output;

public:
	PushButton(std::string, std::string, EventQueue*);
	void checkForEvents(void);
};

#endif /* PERIPHERALS_PUSHBUTTON_HPP_ */

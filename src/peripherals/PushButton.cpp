/*
 * PushButton.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: leon
 */

#include "PushButton.hpp"

PushButton::PushButton(std::string pin_number, std::string name, EventQueue* queue)
{
	event_queue = queue;

	gpio = GPIO(pin_number);
	event_name = name;

	gpio.exportPin();
    gpio.setPinDirection("in");

    gpio.getPinValue(current_input);
    current_output = previous_input = current_input;

}


void PushButton::checkForEvents(void)
{
	previous_input = current_input;
    gpio.getPinValue(current_input);

    if( current_input == previous_input && current_output != current_input)
    {
    	current_output = current_input;

    	if (current_input == "1")
    		event_queue->pushEvent(event_name);
    }

}

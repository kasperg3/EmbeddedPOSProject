/*
 * Timer.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: leon
 */

#include "Timer.hpp"

Timer::Timer(int period, int between_events, std::string name, EventQueue* queue)
{
	event_queue = queue;
	event_name = name;
	us_period = period;
	us_between_events = between_events;
	us_since_last_event = 0;
}

Timer::~Timer()
{

}

void Timer::checkForEvents(void)
{
	us_since_last_event += us_period;

	if(us_since_last_event > us_between_events)
	{
		us_since_last_event -= us_between_events;
		event_queue->pushEvent(event_name);
	}
}

/*
 * EventQueue.cpp
 *
 *  Created on: Sep 30, 2016
 *      Author: leon
 */

#include "../event_handling/EventQueue.hpp"

void EventQueue::pushEvent(std::string event)
{
	event_queue.push(event);
}

void EventQueue::popEvent(std::string& event)
{
	event = event_queue.front();
	event_queue.pop();
}

bool EventQueue::isEmpty()
{
	return event_queue.empty();
}


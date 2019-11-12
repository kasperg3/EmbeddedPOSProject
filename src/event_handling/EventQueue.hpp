//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef EVENT_HANDLING_EVENTQUEUE_HPP_
#define EVENT_HANDLING_EVENTQUEUE_HPP_

#include <queue>
#include <string>
#include <iostream>

class EventQueue
{
private:
	std::queue<std::string> event_queue;

public:
	void pushEvent(std::string);
	void popEvent(std::string&);
	bool isEmpty();
};

#endif /* EVENT_HANDLING_EVENTQUEUE_HPP_ */

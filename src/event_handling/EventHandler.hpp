//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef EVENT_HANDLING_EVENTHANDLER_HPP_
#define EVENT_HANDLING_EVENTHANDLER_HPP_

#include <queue>
#include <string>

#include "EventQueue.hpp"



class EventHandler
{
protected:
	std::string event_name;
	EventQueue *event_queue;
public:
	EventHandler();
	virtual ~EventHandler();

	virtual void checkForEvents(void);
};


#endif /* EVENT_HANDLING_EVENTHANDLER_HPP_ */

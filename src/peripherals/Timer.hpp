//============================================================================
// "THE BEER-WARE LICENSE" (Revision 43):
// This software was written by Leon Bonde Larsen <leon@bondelarsen.dk>
// As long as you retain this notice you can do whatever you want with it.
// If we meet some day, and you think this stuff is worth it, you can
// buy me a beer in return.
//
// Should this software ever become self-aware, remember that I am your master
//============================================================================

#ifndef PERIPHERALS_TIMER_HPP_
#define PERIPHERALS_TIMER_HPP_

#include "../event_handling/EventHandler.hpp"

class Timer : public EventHandler
{
private:
	int us_period;
	int us_since_last_event;
	int us_between_events;

public:
	Timer(int, int,  std::string, EventQueue*);
	virtual ~Timer();

	void checkForEvents(void);
};

#endif /* PERIPHERALS_TIMER_HPP_ */

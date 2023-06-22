#include "DomeEvents.h"

#include <Event.h>

class WoundStart : public Event
{
public:

	WoundStart(Wound w) : Event(WOUND_START)
	{
		std::cout << "PLAYER GOT " + std::to_string(w) + "\n";

		add("WoundStart", w);
	}
};
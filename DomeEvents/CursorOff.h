#include "DomeEvents.h"

#include <Event.h>

class CursorOffInfo : public Event
{
public:

	CursorOffInfo(Wound w) : Event(CURSOR_OFF_INFO)
	{
		std::cout << "PLAYER NOT LOOKING AT " + std::to_string(w) + "\n";

		add("CURSOROFF", w);
	}
};
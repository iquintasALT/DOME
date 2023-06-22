#include "DomeEvents.h"

#include <Event.h>

class CursorOffInfo : public Event
{
public:

	CursorOffInfo() : Event(CURSOR_OFF_INFO)
	{
		std::cout << "PLAYER NOT LOOKING AT UI\n";

		add("CURSOROFF", true);
	}
};
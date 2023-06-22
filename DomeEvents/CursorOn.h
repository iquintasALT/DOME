#include "DomeEvents.h"

#include <Event.h>

class CursorOnInfo : public Event
{
public:

	CursorOnInfo(Wound w) : Event(CURSOR_ON_INFO)
	{
		std::cout << "PLAYER LOOKING AT " + std::to_string(w) + "\n";

		add("CURSORON", w);
	}
};
#pragma once
#include <Event.h>

class WoundStart : public Event
{
public:

	WoundStart() : Event("WOUND_START")
	{
		std::cout << "PLAYER GOT A WOUND\n";
	}
};
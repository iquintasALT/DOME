#pragma once
#include <Event.h>

class CursorOnInfo : public Event
{
public:

	CursorOnInfo() : Event("CURSOR_ON_INFO")
	{
		std::cout << "PLAYER LOOKING AT UI\n";
	}
};
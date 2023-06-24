#pragma once
#include <Event.h>

class Shoot : public Event
{
public:

	Shoot() : Event("SHOOT")
	{
		std::cout << "SHOOT\n";
	}
};
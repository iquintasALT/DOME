#pragma once
#include <Event.h>

class Jump : public Event
{
public:

	Jump() : Event("JUMP")
	{
		std::cout << "JUMP\n";
	}
};

#pragma once
#include <Event.h>

class ReturnHome : public Event
{
public:

	ReturnHome() : Event("RETURN_HOME")
	{
		std::cout << "BACK TO SHELTER\n";

		add("RETURNHOME", true);
	}
};
#include "DomeEvents.h"

#include <Event.h>

class ReturnHome : public Event
{
public:

	ReturnHome(float t) : Event(RETURN_HOME)
	{
		time = t;

		std::cout << "BACK TO SHELTER\n";

		add("RETURNHOME", t);
	}
};
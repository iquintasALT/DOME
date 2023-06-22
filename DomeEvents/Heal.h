#include "DomeEvents.h"

#include <Event.h>

class Heal : public Event
{
public:

	Heal(bool correctItem, bool toxic) : Event(HEAL)
	{	
		std::cout << "PLAYER HEALS ";

		if (correctItem)
			std::cout << " GOOD. ";
		else
			std::cout << " WRONG. ";

		add("CorrectItem", correctItem);

		std::cout << "PLAYER ";

		if (toxic)
			std::cout << " HAS INTOXICATION\n"; 
		else
			std::cout << " HASNT INTOXICATION\n";

		add("Intoxication", toxic);
	}
};
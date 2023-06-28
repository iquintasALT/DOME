#pragma once
#include <Event.h>

class Heal : public Event
{
public:

	Heal(bool correctItem, bool intoxicated, int wounds) : Event("HEAL")
	{	
		std::cout << "PLAYER HEALS ";

		if (correctItem)
			std::cout << " GOOD. ";
		else
			std::cout << " WRONG. ";

		add("CorrectItem", correctItem);

		std::cout << "PLAYER ";

		if (intoxicated)
			std::cout << " HAS INTOXICATION\n"; 
		else
			std::cout << " HASNT INTOXICATION\n";

		add("Intoxication", intoxicated);

		add("Wounds", wounds);
	}
};
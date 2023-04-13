#pragma once
#include <Events.h>
//#include "classes/item.h"

enum Wound { BLEED, PAIN, INTOXICATION, CONTUSION };

class WoundStart : public Events
{
protected:
	Wound wound;

public:

	WoundStart(float timeEvent, Wound w) : Events(timeEvent, WOUND_START)
	{
		wound = w;
		std::cout << "PLAYER GOT " + std::to_string(wound) + "\n";
	}

	std::string serializeToJSON() const;
};

class WoundEnd : public Events
{
protected:
	Wound wound;

public:

	WoundEnd(float timeEvent, Wound w) : Events(timeEvent, WOUND_END)
	{
		wound = w;
		std::cout << "PLAYER GOT RID OF " + std::to_string(wound) + "\n";
	}

	std::string serializeToJSON() const;
};

class Shoot : public Events
{
public:

	Shoot(float timeEvent) : Events(timeEvent, SHOOT)
	{
		std::cout << "SHOOT\n";
	}
};

class Heal : public Events
{
protected:
	ITEMS treatment;

public:

	Heal(float timeEvent, ITEMS t) : Events(timeEvent, HEAL)
	{
		treatment = t;
		std::cout << "PLAYER USED " + std::to_string(treatment) + "\n";
	}

	std::string serializeToJSON() const;
};

class Jump : public Events
{
public:

	Jump(float timeEvent) : Events(timeEvent, JUMP)
	{
		std::cout << "JUMP\n";
	}
};

class ReturnHome : public Events
{
protected:
	float raidTime;

public:

	ReturnHome(float timeEvent, float rTime) : Events(timeEvent, RETURN_HOME)
	{
		raidTime = rTime;
		std::cout << "BACK TO SHELTER\n";
	}

	std::string serializeToJSON() const;
};
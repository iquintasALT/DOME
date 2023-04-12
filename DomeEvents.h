#pragma once
#include <Events.h>

enum Wound { BLEED, PAIN, INTOXICATION, CONTUSION };

class WoundStart : Events
{
protected:
	Wound wound;

public:

	WoundStart(float timeEvent, Wound w) : Events(timeEvent, WOUND_START)
	{
		wound = w;
		std::cout << "PLAYER GOT " + std::to_string(wound) + "\n";
	}

	virtual Events* clone() const;
	virtual std::string serializeToJSON() const;
};

class WoundEnd : Events
{
protected:
	Wound wound;
public:

	WoundEnd(float timeEvent, Wound w) : Events(timeEvent, WOUND_END)
	{
		wound = w;
		std::cout << "PLAYER GOT RID OF " + std::to_string(wound) + "\n";
	}

	virtual Events* clone() const;
	virtual std::string serializeToJSON() const;
};

class Shoot : Events
{
public:

	Shoot(float timeEvent) : Events(timeEvent, SHOOT)
	{
		std::cout << "SHOOT\n";
	}

	virtual Events* clone() const;
	virtual std::string serializeToJSON() const;
};


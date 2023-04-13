#pragma once
#include <Events.h>

enum Wound { BLEED, PAIN, INTOXICATION, CONTUSION };
enum Treatment { ANTIDOTE, BANDAGES, SPLINT, PAINKILLER };

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

	virtual std::string serializeToJSON() const;
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

	virtual std::string serializeToJSON() const;
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
	Treatment treatment;

public:

	Heal(float timeEvent, Treatment t) : Events(timeEvent, HEAL)
	{
		treatment = t;
		std::cout << "PLAYER USED " + std::to_string(treatment) + "\n";
	}

	virtual std::string serializeToJSON() const;
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
public:

	ReturnHome(float timeEvent) : Events(timeEvent, RETURN_HOME)
	{
		std::cout << "BACK TO SHELTER\n";
	}
};
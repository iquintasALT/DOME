#pragma once
#include <Events.h>

enum Wound { BLEED, PAIN, INTOXICATION, CONTUSION };
enum class Treatment { BANDAGE, ANTIDOTE, SPLINT, PAINKILLER };

class SessionStart : public Events
{
public:

	SessionStart() : Events(SESSION_START)
	{
		std::cout << "SESSION START\n";
	}
};

class SessionEnd : public Events
{
public:

	SessionEnd() : Events(SESSION_END)
	{
		std::cout << "SESSION END\n";
	}
};

class WoundStart : public Events
{
protected:
	Wound wound;

public:

	WoundStart(Wound w) : Events(WOUND_START)
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

	WoundEnd(Wound w) : Events(WOUND_END)
	{
		wound = w;
		std::cout << "PLAYER GOT RID OF " + std::to_string(wound) + "\n";
	}

	std::string serializeToJSON() const;
};

class Shoot : public Events
{
public:

	Shoot() : Events(SHOOT)
	{
		std::cout << "SHOOT\n";
	}
};

class Heal : public Events
{
protected:
	Treatment treatment;
	//list<Wound> wounds;

public:

	Heal(Treatment t) : Events(HEAL)
	{
		treatment = t;
		//std::cout << "PLAYER USED " + std::to_string(treatment) + "\n";
	}

	std::string serializeToJSON() const;
};

class Jump : public Events
{
public:

	Jump() : Events(JUMP)
	{
		std::cout << "JUMP\n";
	}
};

class ReturnHome : public Events
{
protected:
	float raidTime;

public:

	ReturnHome(float rTime) : Events(RETURN_HOME)
	{
		raidTime = rTime;
		std::cout << "BACK TO SHELTER\n";
	}

	std::string serializeToJSON() const;
};
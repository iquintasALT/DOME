#pragma once
#include <Events.h>

enum Wound { BLEED, PAIN, INTOXICATION, CONCUSSION };
enum Treatment { T_BANDAGE, T_ANTIDOTE, T_SPLINT, T_PAINKILLER };

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

	nlohmann::json serializeToJSON() const;
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

	nlohmann::json serializeToJSON() const;
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
	std::list<Wound> wounds;

public:

	Heal(Treatment t, std::list<Wound> w) : Events(HEAL)
	{
		treatment = t;
		wounds = w;
		std::cout << "PLAYER USED " + std::to_string(treatment) + "\n";
	}

	nlohmann::json serializeToJSON() const;
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
	std::list<Wound> wounds;

public:

	ReturnHome(float rTime, std::list<Wound> w) : Events(RETURN_HOME)
	{
		raidTime = rTime;
		wounds = w;
		std::cout << "BACK TO SHELTER\n";
	}

	nlohmann::json serializeToJSON() const;
};

class CursorOnInfo : public Events
{
protected:
	Wound wound;

public:

	CursorOnInfo(Wound w) : Events(CURSOR_ON_INFO)
	{
		wound = w;
		std::cout << "PLAYER LOOKING AT " + std::to_string(wound) + "\n";
	}

	nlohmann::json serializeToJSON() const;
};

class CursorOffInfo : public Events
{
protected:
	Wound wound;

public:

	CursorOffInfo(Wound w) : Events(CURSOR_OFF_INFO)
	{
		wound = w;
		std::cout << "PLAYER NOT LOOKING AT " + std::to_string(wound) + "\n";
	}

	nlohmann::json serializeToJSON() const;
};
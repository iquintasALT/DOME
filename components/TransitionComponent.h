#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include <functional>
#include <iostream>

class TransitionComponent: public Component
{
public:
	TransitionComponent(float t, bool fadeOut = true, std::function<void()> f = []() {std::cout << "Transicion destruida"; });
	
	void init() override;
	void update() override;

private:
	bool fadeIn;
	float currentTime;
	float maxTime;
	std::function<void()> function;
	Image* image;
	TextWithBackground* text;
};


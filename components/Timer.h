#pragma once
#include "../ecs/Component.h"
#include <functional>
class Timer : public Component
{
public:
	Timer(float duration, std::function<void()> f);
	void update() override;
private:
	float t;
	float duration;
	std::function<void()> function;
};


#pragma once

#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include <functional>
class HoldToSkip: public Component
{
public:
	HoldToSkip(float maxTime, std::function<void()> f);
	void init() override;
	void update() override;
	void render() override;
private:
	float t;
	float maxT;
	std::function<void()> function;

	Transform* transform;
	Image* image;
};


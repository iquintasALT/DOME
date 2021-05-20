#pragma once

#include "../ecs/Component.h"
#include <functional>

class InitialCameraZoom: public Component
{
public:
	InitialCameraZoom(float zoom, float time, std::function<void()> f = []() {});

	void init() override;
	void update() override;

private:
	float totalTime;
	float initialZoom;
	float targetZoom;

	std::function<void()> function;

	float t;
};


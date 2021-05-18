#pragma once

#include "../ecs/Component.h"

class InitialCameraZoom: public Component
{
public:
	InitialCameraZoom(float zoom, float time);

	void update() override;

private:
	float totalTime;
	float initialZoom;
	float targetZoom;


	float t;
};


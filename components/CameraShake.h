#pragma once
#include "../ecs/Component.h"

#include "../utils/Vector2D.h"
#include <functional>
class CameraShake : public Component
{
public:
	CameraShake(float strength, float speed,  float duration, std::function<void()> f);
	void update() override;

private:
	float strength;
	float duration;
	float speed;
	float t;

	std::function<void()> function;
	Vector2D dir;
};


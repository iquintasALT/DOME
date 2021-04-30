#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../classes/camera.h"

class CameraMovement: public Component
{
public:
	CameraMovement(float velocity_);
	void init() override;
	void update() override;
private:
	float velocity; //0 - 1
	Transform* tr;
	RigidBody* rb;
	Camera* cam;
};


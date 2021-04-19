#pragma once

#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

#include "../components/Transform.h"

class CameraMovement: public Component
{
private:
	Transform* player;
	Transform* tr;
protected:
	Vector2D a;
public:
	inline CameraMovement() :player(nullptr), tr(nullptr){};
	void init() override;
	void update() override;
	inline void setPlayer(Transform* p) { player = p; };
};


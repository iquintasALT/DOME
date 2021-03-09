#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"

class GravityComponent : public Component {
public:
	GravityComponent() {
		gravity = 1;
	};

	GravityComponent(float gr) {
		gravity = gr;
	};

	virtual void update();
private:
	Transform* entityTr;
	float gravity;
};

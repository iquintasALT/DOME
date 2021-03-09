#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"

class KeyboardPlayerCtrl : public Component {
public:
	KeyboardPlayerCtrl() {
		speed = 1;
	};

	KeyboardPlayerCtrl(float sp) {
		speed = sp;
	};

	virtual void update();
private:
	Transform* entityTr;
	float speed;
};


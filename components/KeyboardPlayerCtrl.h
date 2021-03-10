#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"

class KeyboardPlayerCtrl : public Component {
public:
	KeyboardPlayerCtrl() {
		speed = consts::PLAYER_SPEED;
		entityTr = nullptr;
	};

	virtual void init() {
		entityTr = entity_->getComponent<Transform>();
		assert(entityTr != nullptr);
	}

	virtual void update();

private:
	Transform* entityTr;
	float speed;
};


#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"

class KeyboardPlayerCtrl : public Component {
public:
	KeyboardPlayerCtrl() {
		speed = consts::PLAYER_SPEED;
		entityTr = nullptr;
		left = right = crouched = false;
	};

	virtual void init() {
		entityTr = entity_->getComponent<Transform>();
		assert(entityTr != nullptr);
	}
	virtual void update();

	void resetSpeed();
private:
	Transform* entityTr;
	float speed;
	bool left, right, crouched;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
};


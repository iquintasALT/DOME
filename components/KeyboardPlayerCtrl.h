#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../classes/particleSystem.h"
#include "../sdlutils/SDLUtils.h"

#include "rigid_body.h"
#include "Transform.h"

class KeyboardPlayerCtrl : public Component {
private:
	RigidBody* rb_;
	Transform* tr_;
	
	float speed;
	float jumpSpeed;
	bool left, right, crouched;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

public:
	KeyboardPlayerCtrl();

	virtual void init();

	virtual void update();

	inline bool isCrouching() { return crouched; }

	void resetSpeed();
	float getSpeed();
	void setSpeed(float speed);
	void setJumpSpeed(float jumpSpeed);
};


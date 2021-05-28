#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../components/particle_system.h"
#include "../sdlutils/SDLUtils.h"

#include "rigid_body.h"
#include "transform.h"

class KeyboardPlayerCtrl : public Component {
private:
	RigidBody* rb_;
	Transform* tr_;

	Transform* darkArea;

	float speed;
	float maxSpeed;
	float jumpSpeed;
	float acceleration;
	float deceleration;
	float stairsSpeed;
	float cooldown;
	bool left, right, crouched, up, down, onLadderTrigger, onLadder, xClicked, spaceDown;
	bool walking, climbing;
	Vector2D stairPosition, stairSize;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	void OnCollision(Entity* bc) override;
	void OnTrigger(Entity* bc) override;

public:
	KeyboardPlayerCtrl();

	virtual void init();

	virtual void update();

	inline bool isCrouching() { return crouched; }
	inline bool isClimbingLadder() { return onLadder; };
	inline bool isWalking() { return walking; };

	void resetSpeed();
	float getSpeed();
	float getMaxSpeed();
	void setSpeed(float speed);
	void setMaxSpeed(float speed_);
	void setJumpSpeed(float jumpSpeed);
};


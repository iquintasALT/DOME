#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../components/particleSystem.h"
#include "../sdlutils/SDLUtils.h"

#include "rigid_body.h"
#include "Transform.h"

class KeyboardPlayerCtrl : public Component {
private:
	RigidBody* rb_;
	Transform* tr_;
	
	float speed;
	float jumpSpeed;
	float stairsSpeed;
	bool left, right, crouched, up, down, inStairTrigger, inStair, xClicked, spaceDown;
	Vector2D stairPosition, stairSize;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	void OnCollision(Entity* bc) override;
	void OnTrigger(Entity* bc) override;

public:
	KeyboardPlayerCtrl();

	virtual void init();

	virtual void update();

	inline bool isCrouching() { return crouched; }
    inline bool isStairs() { return inStair; };
	
	void resetSpeed();
	float getSpeed();
	void setSpeed(float speed);
	void setJumpSpeed(float jumpSpeed);
};


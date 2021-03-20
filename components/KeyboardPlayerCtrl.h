#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/GravityComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../game/checkML.h"
#include "../game/constant_variables.h"
#include "../ecs/Manager.h"
#include "../classes/particleSystem.h"
#include "../sdlutils/SDLUtils.h"

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

		gravity_ = entity_->getComponent<GravityComponent>();
		assert(entityTr != nullptr);

		dust = entity_->getComponent<ParticleSystem>();
		assert(dust != nullptr);
	}
	virtual void update();
	inline bool isCrouching() { return crouched; }
	void resetSpeed();
private:
	Transform* entityTr;
	GravityComponent* gravity_;
	float speed;
	bool left, right, crouched;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	ParticleSystem* dust;
};


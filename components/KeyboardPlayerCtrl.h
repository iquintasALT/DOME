#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../game/checkML.h"
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

		Entity* particles = entity_->getMngr()->addEntity();
		dustTr = particles->addComponent<Transform>(Vector2D(0, 0), Vector2D(), 30, 30, 0);
		dust = particles->addComponent<ParticleSystem>(entityTr, &sdlutils().images().at("player"), 3, 14, 0, 0);
	}
	virtual void update();

	void resetSpeed();
private:
	Transform* entityTr;
	float speed;
	bool left, right, crouched;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	ParticleSystem* dust;
	Transform* dustTr;
};


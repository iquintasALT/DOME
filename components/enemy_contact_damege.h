#include "../components/interactableElement.h"

#include "../ecs/Component.h"
#include "../Components/Transform.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"

#pragma once
class Manager;
class EnemyContactDamage : public Component
{
private:
	Manager* manager;
	Transform* tr;
	float cooldown;
	bool collision;
public:
	EnemyContactDamage() : manager(nullptr), tr(nullptr) { collision = false; cooldown = 0; };
	inline bool isOnCooldown() { return collision; };
	void update() override;
	void init() override;
};





#include "../ecs/Component.h"
#include "../Components/Transform.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"

class Physiognomy;
#pragma once
class Manager;
class EnemyContactDamage : public Component
{
private:
	Transform* tr;
	float cooldown;
	bool canCollide;
	Physiognomy* physiognomy;
	void OnCollision(Entity* collider) override;
public:
	EnemyContactDamage(Physiognomy* physiognomy_) : tr(nullptr), physiognomy(physiognomy_) { canCollide = false; cooldown = 0; };
	inline bool isOnCooldown() { return canCollide; };
	void init() override;
	void update() override;
};





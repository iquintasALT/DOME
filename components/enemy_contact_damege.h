#include "../components/interactableElement.h"

#include "../ecs/Component.h"
#include "../Components/Transform.h"
#include "../game/checkML.h"

#pragma once
class Manager;
class EnemyContactDamage : public Component
{
private:
	Manager* manager;
	Transform* tr;
public:
	EnemyContactDamage() : manager(nullptr), tr(nullptr) {};
	void update() override;
	void init() override;
};





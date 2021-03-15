#pragma once
//#include "../ecs/Component.h"
//#include "../ecs/Entity.h"
//#include "../components/Transform.h"
//#include "../game/constant_variables.h"
//#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
//#include "../components/Image.h"
//#include "../sdlutils/SDLUtils.h"
#include "../classes/game_entity.h"
#include "../game/ecs_defs.h"
//#include "../ecs/Manager.h"
#include "../components/weapon.h"

#include <math.h>

class WeaponBehaviour : public GameEntity {
public:
	WeaponBehaviour(float fireRate, float dmg, Manager* mngr, Vector2D playerPos, Transform* playerTr);

private:
	float dmg_;
};
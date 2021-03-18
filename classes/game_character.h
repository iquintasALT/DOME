#pragma once
#ifndef GAMECHARACTER_H_
#define GAMECHARACTER_H_

#include "game_entity.h"
#include "../game/checkML.h"
/*#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/InventoryController.h"
#include "../components/Inventory.h"*/
class Manager;
class GameCharacter :
    public GameEntity
{
public:
    GameCharacter(Manager* mngr_) : GameEntity(mngr_) {}
};

#endif
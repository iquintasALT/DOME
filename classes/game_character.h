#pragma once
#include "game_entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/InventoryController.h"
#include "../components/Inventory.h"

class GameCharacter :
    public GameEntity
{
public:
    GameCharacter(Manager* mngr_) : GameEntity(mngr_) {}
};


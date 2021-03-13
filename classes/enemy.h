#pragma once
#include "game_character.h"
class Enemy :
    public GameCharacter
{
public:
    static Entity* newEnemy(Manager* mngr_, Point2D pos)
    {
        Entity* enemy = mngr_->addEntity();
        enemy->addComponent<Transform>(pos, Vector2D(), 32, 64, 0);
        enemy->addComponent<GravityComponent>();
        enemy->addComponent<Image>(&sdlutils().images().at("player"), 2, 14, 0, 0);
        enemy->addComponent<player_animation>();
        return enemy;
    }
};


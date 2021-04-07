#pragma once
#include "enemy_component.h"
#include "../utils/Vector2D.h"
class Transform;
class EnemyAttackComponent :
    public EnemyComponent
{
    friend EnemyBehaviourComponent;
protected:
    Transform* tr_;
    Transform* playerTr_;

    virtual void attack() = 0;
    // Returns a vector pointing towards the player
    Vector2D getTarget();
public:
    virtual void update() override = 0;
    virtual void init() override;
};


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

    // attack is bool so that behaviour knows whether to start attack cooldown
    virtual bool attack() = 0;
    // Returns a vector pointing towards the player
    Vector2D getTarget();
public:
    virtual void update() override = 0;
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------

class GroundedMeleeAttack :
    public EnemyAttackComponent
{
protected:
    // When the enemy performs its attack, it will lunge at the player with this boost of speed
    Vector2D lunge = Vector2D();
    // Distance from which the enemy can attack
    float reach;

    /// Leaps at player, entering attack mode
    virtual bool attack();
};
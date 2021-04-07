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

    EnemyAttackComponent(Transform* transform = nullptr, Transform* playerTransform = nullptr) : 
        tr_(transform), playerTr_(playerTransform) {};
    // attack is bool so that behaviour knows whether to start attack cooldown
    virtual bool attack() = 0;
    // Returns a vector pointing towards the player
    Vector2D getTarget();
public:
    virtual void update() override = 0;
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------

class MeleeAttack :
    public EnemyAttackComponent
{
protected:
    /// When the enemy performs its attack, it will lunge at the player with this boost of speed
    /// Both values should be positive, and only represent magnitude
    Vector2D lunge;

    /// Leaps at player, entering attack mode
    virtual bool attack() override;
public:
    MeleeAttack(Vector2D lungeThrust = Vector2D(3.0, 2.0)) : lunge(lungeThrust) {};
};

//--------------------------------------------------------------------------------------------------------------

class GroundedMeleeAttack :
    public MeleeAttack
{
protected:
    virtual bool attack() override;
public:
    GroundedMeleeAttack(Vector2D lungeThrust = Vector2D(3.0, 2.0)) : MeleeAttack(lungeThrust) {};
};
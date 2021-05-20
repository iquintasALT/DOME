#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "rigid_body.h"

class Transform;
class EnemyAnimation;

class EnemyAttackComponent : public Component
{
    friend EnemyBehaviourComponent;
protected:
    Transform* tr_;
    Transform* playerTr_;
    RigidBody* rb_;
    
    // attack is bool so that behaviour knows whether to start attack cooldown
    virtual bool attack() { return false; };
    // Returns a vector pointing towards the player
    Vector2D getTarget();
public:
    EnemyAttackComponent(Transform* transform = nullptr, Transform* playerTransform = nullptr) : 
        tr_(transform), playerTr_(playerTransform) {};
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------

class MeleeAttack : public EnemyAttackComponent
{
protected:
    /// When the enemy performs its attack, it will lunge at the player with this boost of speed
    /// Both values should be positive, and only represent magnitude
    Vector2D lunge;

    /// Leaps at player, entering attack mode
    virtual bool attack() override;
public:
    MeleeAttack(Vector2D lungeThrust = Vector2D(4.0, 2.0)) : lunge(lungeThrust) {};
};

//--------------------------------------------------------------------------------------------------------------

class GroundedMeleeAttack : public MeleeAttack
{
protected:
    virtual bool attack() override;
    EnemyAnimation* animator;
public:
    GroundedMeleeAttack(Vector2D lungeThrust = Vector2D(4.0, 2.0)) : MeleeAttack(lungeThrust) {};
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------
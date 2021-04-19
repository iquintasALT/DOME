#ifndef ENEMYBEHAVIOUR_H_
#define ENEMYBEHAVIOUR_H_

#include "enemy_component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/ray_cast.h"
#include "../utils/checkML.h"
#include "../components/enemy_detection_component.h"
#include "../game/constant_variables.h"


class Transform;
class RigidBody;
class EnemyAttackComponent;

class EnemyBehaviourComponent : public EnemyComponent
{
protected:
    Transform* playerTr_;
    Transform* tr_;
    RigidBody* rb_ = nullptr;
    EnemyDetectionComponent* enemyDetection_;
    EnemyAttackComponent* attack_ = nullptr;
    // Movement speed
    float speed_; 
    float attackDistance_;
    // ms between attacks
    short int attackCooldown_;
    // Time of last attack
    unsigned long int lastAttack_ = 0;


public:
    inline EnemyBehaviourComponent(float speed = consts::MELEE_ENEMY_SPEED, 
        float attackDistance = consts::MELEE_ENEMY_STOPDISTANCE, 
        short int attackCooldown = consts::ENEMY_ATTACK_COOLDOWN) : 
        playerTr_(nullptr), tr_(nullptr), enemyDetection_(nullptr), speed_(speed), 
        attackDistance_(attackDistance), attackCooldown_(attackCooldown) {};

    inline virtual void update() override = 0;
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------
//Follows player on X axis anytime it is further than attackDistance from player
class ChasePlayer : public EnemyBehaviourComponent
{
public:
    ChasePlayer(float speed, float attackDistance);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------
//Maintains distance from the player within a margin: no closer than marginDistance and no further than attackDistance
class KeepDistance : public EnemyBehaviourComponent {
protected:
    float marginDistance_;

public:
    KeepDistance(float speed, float marginDistance, float attackDistance);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------
/// While far from the player, maintains hoverHeight above the closest floor
/// When it comes within attackDistance of player, it will begin to match the player's altitude
/// Stops still when within stopDistance of the player
class FlyingChasePlayer : public EnemyBehaviourComponent
{
protected:
    float hoverHeight_;
    float approachDistance_; //Distance at which the enemy will begin to lose altitude to attack player

public:
    FlyingChasePlayer(float speed, float attackDistance, float hoverHeight, float approachDistance);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------

#endif
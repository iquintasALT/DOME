#ifndef ENEMYBEHAVIOUR_H_
#define ENEMYBEHAVIOUR_H_

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/ray_cast.h"

#include "../utils/checkML.h"
#include "../components/enemy_detection_component.h"

#include "enemy_component.h"

class Transform;
class RigidBody;

class EnemyBehaviourComponent : public EnemyComponent
{
protected:
    Transform* playerTr_;
    Transform* tr_;
    RigidBody* rb_;
    EnemyDetectionComponent* enemyDetection;

public:
    inline EnemyBehaviourComponent() : playerTr_(nullptr), tr_(nullptr), enemyDetection(nullptr) {};
    inline virtual void update() override = 0;
    virtual void init() override;
};

//--------------------------------------------------------------------------------------------------------------
//Follows player on X axis anytime it is further than stopDistance from player
class ChasePlayer : public EnemyBehaviourComponent
{
protected:
    float speed;
    float stopDistance;

public:
    ChasePlayer(float speed_, float stopDistance_);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------
//Maintains distance from the player within a margin: no closer than marginDistance and no further than shootDistance
class KeepDistance : public EnemyBehaviourComponent {
protected:
    float speed;
    float marginDistance;
    float shootDistance;

public:
    KeepDistance(float speed, float marginDistance, float shootDistance);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------
/// While far from the player, maintains hoverHeight above the closest floor
/// When it comes within attackDistance of player, it will begin to match the player's altitude
/// Stops still when within stopDistance of the player
class FlyingChasePlayer : public EnemyBehaviourComponent
{
protected:
    float speed;
    float stopDistance;
    float hoverHeight;
    float attackDistance; //Distance at which the enemy will begin to lose altitude to attack player

public:
    FlyingChasePlayer(float speed_, float stopDistance_, float hoverHeight_, float attackDistance_);
    virtual void update() override;
};

//--------------------------------------------------------------------------------------------------------------

#endif
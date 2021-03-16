#ifndef ENEMYBEHAVIOUR_H_
#define ENEMYBEHAVIOUR_H_
#include "enemy_component.h"

class Player;
class EnemyBehaviourComponent :
    public EnemyComponent
{
protected:
    Transform* playerTr;
    Transform* entityTr;
public:
    virtual void update() override = 0;
    virtual void init() override;
};

class ChasePlayer :
    public EnemyBehaviourComponent
{
protected:
    float speed;
    float stopDistance;
public:
    ChasePlayer(float speed_, float stopDistance_);
    virtual void update() override;
};
#endif
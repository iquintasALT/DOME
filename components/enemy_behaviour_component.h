#ifndef ENEMYBEHAVIOUR_H_
#define ENEMYBEHAVIOUR_H_
#include "enemy_component.h"
#include "../game/checkML.h"
#include "../components/enemy_detection_component.h"

class Player;
class EnemyBehaviourComponent :
    public EnemyComponent
{
protected:
    Transform* playerTr;
    Transform* entityTr;
    EnemyDetectionComponent* enemyDetection;
public:
    EnemyBehaviourComponent() : playerTr(nullptr), entityTr(nullptr) {};
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

class KeepDistance : public EnemyBehaviourComponent {
protected:
    float speed;
    float marginDistance;
    float shootDistance;
public:
    KeepDistance(float speed, float marginDisntace, float shootDistance);
    virtual void update() override;
};
#endif
#ifndef ENEMYBEHAVIOUR_H_
#define ENEMYBEHAVIOUR_H_
#include "enemy_component.h"

class EnemyBehaviourComponent :
    public EnemyComponent
{
protected:
    Transform* entityTr;
public:
    virtual void update() override = 0;
    virtual void init() override;
};
#endif
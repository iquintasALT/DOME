#pragma once
#include "enemy_component.h"
class Transform;
class EnemyAttackComponent :
    public EnemyComponent
{
protected:
    Transform* tr_;
    Transform* playerTr_;
public:
    virtual void update() override = 0;
    virtual void init() override;
};


#pragma once
#include "GameObject.h"
#include "PhysicsObject.h"
class Entity :
    public GameObject,
    public PhysicsObject
{
};


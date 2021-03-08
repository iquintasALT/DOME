#pragma once
#include "GameCharacter.h"
#include "EventHandler.h"
#include "Inventory.h"
#include "../components/PlayerHealthComponent.h"
#include "Item.h"
class Player :
    public GameCharacter,
    public EventHandler
{
public:
    Player();
    virtual void render();

};

class Physiognomy
{

};

class Weapon :
    public ItemInfo
{

};
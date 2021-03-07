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
};

class Physiognomy
{

};

class Weapon :
    public ItemInfo
{

};
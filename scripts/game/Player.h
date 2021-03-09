#pragma once
#include "game_character.h"
#include "event_handler.h"
#include "inventory.h"
#include "../components/player_health_component.h"
#include "item.h"
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
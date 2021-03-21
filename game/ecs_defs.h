// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../game/checkML.h"

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class GravityComponent;
class KeyboardPlayerCtrl;
class player_animation;
class Weapon;
class InventoryController;
class Inventory;
class GameEntityComponent;
class EnemyComponent;
class EnemyBehaviourComponent;
class ChasePlayer;
class TileRenderer;
class KeepDistance;
class DistanceDetection;
class RayCastDetection;
class Interactions;
class InteractableElement;
class ParticleSystem;
class Ricochet;
class Loot;
class RicochetWeapon;
class PlayerCollisions;
class PlayerHealthComponent;
class HungerComponent;
class TirednessComponent;
class ChargeWeapon;
class Charge;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	GravityComponent,\
	KeyboardPlayerCtrl,\
	player_animation,\
    Weapon, \
	InventoryController, \
	Inventory, \
	GameEntityComponent, \
	EnemyComponent, \
	EnemyBehaviourComponent, \
	ChasePlayer, \
	TileRenderer, \
	KeepDistance,\
	DistanceDetection,\
	RayCastDetection,\
	Interactions, \
	Ricochet,\
	InteractableElement, \
	ParticleSystem, \
	Loot, \
    RicochetWeapon, \
	PlayerHealthComponent,\
	HungerComponent,\
	TirednessComponent,\
	PlayerCollisions, \
	ChargeWeapon, \
	Charge

// groups

struct Wall_grp;
#define _GRPS_LIST_  Wall_grp

// handlers
struct Player_hdlr;
#define _HDLRS_LIST_ Player_hdlr
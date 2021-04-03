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
class EnemyComponent;
class EnemyBehaviourComponent;
class ChasePlayer;
class KeepDistance;
class FlyingChasePlayer;
class TileRenderer;
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
class BoxCollider;
class BledoutComponent;
class RigidBody;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	GravityComponent, \
	KeyboardPlayerCtrl, \
	player_animation, \
    Weapon, \
	InventoryController, \
	Inventory, \
	EnemyComponent, \
	EnemyBehaviourComponent, \
	ChasePlayer, \
	KeepDistance, \
	FlyingChasePlayer, \
	TileRenderer, \
	DistanceDetection, \
	RayCastDetection, \
	Interactions, \
	Ricochet,\
	InteractableElement, \
	ParticleSystem, \
	Loot, \
    RicochetWeapon, \
	PlayerHealthComponent,\
	HungerComponent, \
	TirednessComponent, \
	PlayerCollisions, \
	ChargeWeapon, \
	Charge, \
	BoxCollider,\
	BledoutComponent, \
    RigidBody

// groups

struct Wall_grp;
struct Contact_Dmg_grp;
#define _GRPS_LIST_  \
	Wall_grp, \
	Contact_Dmg_grp

// handlers
struct Player_hdlr;
#define _HDLRS_LIST_ Player_hdlr
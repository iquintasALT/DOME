// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/checkML.h"

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class KeyboardPlayerCtrl;
class player_animation;
class enemy_animation;
class Weapon;
class InventoryController;
class Inventory;
class EnemyComponent;
class EnemyBehaviourComponent;
class ChasePlayer;
class KeepDistance;
class FlyingChasePlayer;
class EnemyAttackComponent;
class MeleeAttack;
class GroundedMeleeAttack;
class RangedAttack;
class TileRenderer;
class DistanceDetection;
class RayCastDetection;
class Interactions;
class InteractableElement;
class Loot;
class BackToShelter;
class ParticleSystem;
class Ricochet;
class RicochetWeapon;
class PlayerCollisions;
class PlayerHealthComponent;
class HungerComponent;
class TirednessComponent;
class ChargeWeapon;
class Charge;
class BoxCollider;
class BleedoutComponent;
class PainComponent;
class ConcussionComponent;
class IntoxicationComponent;
class RigidBody;
class EnemyContactDamage;
class HypothermiaComponent;
class ClassicBullet;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	KeyboardPlayerCtrl, \
	player_animation, \
	enemy_animation, \
    Weapon, \
	InventoryController, \
	Inventory, \
	EnemyComponent, \
	EnemyBehaviourComponent, \
	ChasePlayer, \
	KeepDistance, \
	FlyingChasePlayer, \
	EnemyAttackComponent, \
	MeleeAttack, \
	GroundedMeleeAttack, \
	RangedAttack, \
	TileRenderer, \
	DistanceDetection, \
	RayCastDetection, \
	Interactions, \
	Ricochet,\
	InteractableElement, \
	Loot, \
	BackToShelter, \
	ParticleSystem, \
    RicochetWeapon, \
	PlayerHealthComponent,\
	HungerComponent, \
	TirednessComponent, \
	PlayerCollisions, \
	ChargeWeapon, \
	Charge, \
	BoxCollider,\
	BleedoutComponent,\
	PainComponent,\
	ConcussionComponent,\
	IntoxicationComponent,\
    RigidBody,\
	EnemyContactDamage,\
	HypothermiaComponent,\
	ClassicBullet

// groups

struct Wall_grp;
struct Enemy_grp;
struct Stairs_grp;
#define _GRPS_LIST_  \
	Wall_grp, \
	Enemy_grp, \
	Stairs_grp
	

// handlers
struct Player_hdlr;
#define _HDLRS_LIST_ Player_hdlr

// collision layers
//struct CollLayer1;
//#define _COLLISIONS_LIST_ CollLayer1

// render layers
struct Default;
struct Background;
struct Walls;
struct Player;
struct Enemy;
struct Bullets;
struct Loot;
struct Interface;
struct Item;
#define _RENDER_LIST_ \
	Background, \
	Default, \
	Walls, \
	Player, \
	Enemy, \
	Bullets, \
	Loot, \
	Interface, \
	Item
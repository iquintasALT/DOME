// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../utils/checkML.h"

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class Fade;
class KeyboardPlayerCtrl;
class player_animation;
class EnemyAnimation;
class FlyingEnemyAnimation;
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
class TextWithBackground;
class Open_station;
class TransitionComponent;
class CameraMovement;
class ScrollingBackGround;
class ChangeImage;
class ParallaxComponent;
#define _CMPS_LIST_  \
	Transform,\
	Image,\
	Fade,\
	KeyboardPlayerCtrl, \
	player_animation, \
	EnemyAnimation, \
	FlyingEnemyAnimation, \
    Weapon, \
	InventoryController, \
	Inventory, \
	EnemyComponent, \
	EnemyBehaviourComponent, \
	ChasePlayer, \
	KeepDistance, \
	FlyingChasePlayer, \
	EnemyAttackComponent, \
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
	ClassicBullet, \
	TextWithBackground,\
	TransitionComponent, \
	Open_station, \
	CameraMovement, \
	ScrollingBackGround, \
	ChangeImage,\
	ParallaxComponent

// groups

struct Wall_grp;
struct Enemy_grp;
struct Ladders_grp;
struct Player_grp;
struct DefaultEnemy_grp;
struct FlyingEnemy_grp;
struct RangedEnemy_grp;
#define _GRPS_LIST_  \
	Wall_grp, \
	Enemy_grp, \
	Ladders_grp, \
	Player_grp, \
	DefaultEnemy_grp, \
	FlyingEnemy_grp, \
	RangedEnemy_grp


// handlers
struct Player_hdlr;
#define _HDLRS_LIST_ Player_hdlr

// collision layers
//struct CollLayer1;
//#define _COLLISIONS_LIST_ CollLayer1

// render layers
struct Default;
struct Parallax;
struct Background;
struct Walls;
struct Player;
struct Enemy;
struct Bullets;
struct Loot;
struct Dark;
struct Interface;
struct Item;
struct ULTIMATE;
#define _RENDER_LIST_ \
	Parallax,\
	Background, \
	Default, \
	Walls, \
	Player, \
	Enemy, \
	Bullets, \
	Loot, \
	Dark,\
	Interface, \
	Item, \
	ULTIMATE

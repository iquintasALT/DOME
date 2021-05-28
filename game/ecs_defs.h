#pragma once
#include "../utils/checkML.h"

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class KeyboardPlayerCtrl;
class PlayerAnimation;
class EnemyAnimation;
class FlyingEnemyAnimation;
class Weapon;
class WeaponAnimation;
class InventoryController;
class Inventory;
class EnemyBehaviourComponent;
class ChasePlayer;
class KeepDistance;
class FlyingChasePlayer;
class EnemyAttackComponent;
class MeleeAttack;
class GroundedMeleeAttack;
class DistanceDetection;
class RayCastDetection;
class Interactions;
class InteractableElement;
class Loot;
class BackToShelter;
class ParticleSystem;
class Ricochet;
class RicochetWeapon;
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
class OpenStation;
class TransitionComponent;
class CameraMovement;
class ScrollingBackGround;
class ChangeImage;
class ParallaxComponent;
class HoldToSkip;
class InitialCameraZoom;
class Dialogue;
class CameraShake;
class Timer;
class TutorialLoot;
class TutorialManager;
class TutorialTrigger;
class TutorialCameraMovement;
class TutorialBackToShelter;
#define _CMPS_LIST_  \
	Transform,\
	Image,\
	KeyboardPlayerCtrl, \
	PlayerAnimation, \
	EnemyAnimation, \
	FlyingEnemyAnimation, \
    Weapon, \
    WeaponAnimation, \
	InventoryController, \
	Inventory, \
	EnemyBehaviourComponent, \
	ChasePlayer, \
	KeepDistance, \
	FlyingChasePlayer, \
	EnemyAttackComponent, \
	DistanceDetection, \
	RayCastDetection, \
	Interactions, \
	Ricochet,\
	InteractableElement, \
	Loot, \
	BackToShelter, \
	ParticleSystem, \
	PlayerHealthComponent,\
	HungerComponent, \
	TirednessComponent, \
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
	OpenStation, \
	CameraMovement, \
	ScrollingBackGround, \
	ChangeImage,\
	ParallaxComponent,\
	HoldToSkip, \
	InitialCameraZoom, \
	Dialogue, \
	CameraShake, \
	Timer, \
	TutorialLoot, \
	TutorialManager, \
	TutorialTrigger, \
	TutorialCameraMovement, \
	TutorialBackToShelter

// groups

struct Wall_grp;
struct Enemy_grp;
struct Ladders_grp;
struct Player_grp;
struct DefaultEnemy_grp;
struct FlyingEnemy_grp;
struct INITIALGRP;
#define _GRPS_LIST_  \
	Wall_grp, \
	Enemy_grp, \
	Ladders_grp, \
	Player_grp, \
	DefaultEnemy_grp, \
	FlyingEnemy_grp, \
	INITIALGRP
	


// handlers
struct Player_hdlr;
#define _HDLRS_LIST_ Player_hdlr

// render layers
struct Parallax;
struct Background;
struct Default;
struct Walls;
struct Loot;
struct Player;
struct Enemy;
struct Bullets;
struct Dark;
struct Item;
struct Interface;
struct ULTIMATE;
#define _RENDER_LIST_ \
	Parallax,\
	Background, \
	Default, \
	Walls, \
	Loot, \
	Player, \
	Enemy, \
	Bullets, \
	Dark,\
	Interface, \
	Item, \
	ULTIMATE

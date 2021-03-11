// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class GravityComponent;
class KeyboardPlayerCtrl;
class player_animation;
class WeaponBehaviour;

#define _CMPS_LIST_  \
	Transform,\
	Image,\
	GravityComponent,\
	KeyboardPlayerCtrl,\
	player_animation,\
    WeaponBehaviour


// groups

struct Group_1;
#define _GRPS_LIST_  Group_1

// handlers
struct Player;
#define _HDLRS_LIST_ Player

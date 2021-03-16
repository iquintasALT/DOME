// This file is part of the course TPV2@UCM - Samir Genaim

// DO NOT USE/MODIFY THIS FILE, IT IS JUST AN EXAMPLE OF HOW YOUR
// ecs_defs.h should look like

#pragma once
#include "../game/checkML.h"

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Image;
class PacManCtrl;
#define _CMPS_LIST_  Transform,Image,PacManCtrl

// groups -- forward declaration, but they are never defined as data structures
struct Ghost;
struct Cheery;
#define _GRPS_LIST_  Ghost,Cheery

// handlers -- forward declaration, but they are never defined as data structures
struct Blinky;
struct Pinky;
#define _HDLRS_LIST_ Blinky,Pinky


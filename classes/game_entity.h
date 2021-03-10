#pragma once
#include "game_object.h"
class GameEntity :
    public GameObject
{
protected:
	Vector2D velocity = Vector2D();
	float mass = 0;
	//TO DO
	//SpriteRenderer* spriteRenderer
public:
	Vector2D getVelocity() { return velocity; };
	void setVelocity(Vector2D newVelocity) { size = newVelocity; };
	void scale(float scale) { size = size * scale; };
	void update() override {};
};


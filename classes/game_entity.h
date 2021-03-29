#pragma once
#include "game_object.h"
#include "../game/checkML.h"

class GameEntity : public GameObject
{
protected:
	Vector2D velocity = Vector2D();
	float mass = 0;
	//TO DO
	//addComponent<Image>(...);
public:
	inline GameEntity(Manager* mngr_) : GameObject(mngr_) {};
	inline Vector2D getVelocity() { return velocity; };
	inline void setVelocity(Vector2D newVelocity) { size = newVelocity; };
	inline void scale(float scale) { size = size * scale; };
	//void update() override {};
};


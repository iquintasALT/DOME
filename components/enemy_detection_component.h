#pragma once
#include "enemy_component.h"
#include "../game/checkML.h"

class EnemyDetectionComponent : public EnemyComponent {
protected:
	Transform* playerTr;
	Transform* entityTr;
	bool activeEnemy;
public:
	EnemyDetectionComponent() : playerTr(nullptr), entityTr(nullptr), activeEnemy(false){};
	virtual void update() override = 0;
	virtual void init() override;
	void setActive(bool active) { activeEnemy = active; }
	bool isActive() { return activeEnemy; }
};

class DistanceDetection : public EnemyDetectionComponent {
protected:
	float distance;
public:
	DistanceDetection(float distance);
	virtual void update() override;
};
class RayCastDetection : public EnemyDetectionComponent {
	RayCastDetection() {};
};


#pragma once
#include "../ecs/Component.h"

#include "../utils/checkML.h"

class Transform;

class EnemyDetectionComponent : public Component {
protected:
	Transform* playerTr;
	Transform* tr_;
	bool activeEnemy;

public:
	inline EnemyDetectionComponent() : playerTr(nullptr), tr_(nullptr), activeEnemy(false) {};
	virtual void update() override = 0;
	virtual void init() override;
	inline void setActive(bool active) { activeEnemy = active; }
	inline bool isActive() { return activeEnemy; }
};

class DistanceDetection : public EnemyDetectionComponent {
protected:
	float distance;

public:
	DistanceDetection(float distance);
	virtual void update() override;
	void setDistance(float dist);
};

class RayCastDetection : public EnemyDetectionComponent {
	inline RayCastDetection() {};
};


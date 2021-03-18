#include "enemy_detection_component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void EnemyDetectionComponent::init() {
	playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	entityTr = entity_->getComponent<Transform>();
	assert(playerTr != nullptr && entityTr != nullptr);
}

DistanceDetection::DistanceDetection(float distance_) : distance(distance_) {};

void DistanceDetection::update() {
	float distanceToPlayer = std::abs(std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()));

	if (activeEnemy) {
		if (distanceToPlayer > distance * 2) {
			activeEnemy = false;
		}
	}
	else if (distanceToPlayer < distance) activeEnemy = true;
}
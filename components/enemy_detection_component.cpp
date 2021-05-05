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

void DistanceDetection::setDistance(float dist) {
	distance = dist;
}

void DistanceDetection::update() {
	float distanceToPlayerX = std::abs(std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()));
	float distanceToPlayerY = std::abs(std::abs(playerTr->getPos().getY() - entityTr->getPos().getY()));

	if (activeEnemy) {
		if (distanceToPlayerX > distance * 2 && distanceToPlayerY > distance * 2) activeEnemy = false;
	}
	else if (distanceToPlayerX < distance || distanceToPlayerY < distance) activeEnemy = true;
}
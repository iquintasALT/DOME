#include "enemy_detection_component.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "transform.h"
#include "rigid_body.h"


void EnemyDetectionComponent::init() {
	playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	tr_ = entity_->getComponent<Transform>();
	activeEnemy = false;
	assert(playerTr != nullptr && tr_ != nullptr);
}

DistanceDetection::DistanceDetection(float distance_) : distance(distance_) {};

void DistanceDetection::setDistance(float dist) {
	distance = dist;
}

void DistanceDetection::update() {
	float distanceToPlayerX = std::abs(std::abs(playerTr->getPos().getX() - tr_->getPos().getX()));
	float distanceToPlayerY = std::abs(std::abs(playerTr->getPos().getY() - tr_->getPos().getY()));

	if (activeEnemy) {
		if (distanceToPlayerX > distance * 2 && distanceToPlayerY > distance * 2) activeEnemy = false;
	}
	else if (distanceToPlayerX < distance || distanceToPlayerY < distance) activeEnemy = true;
}
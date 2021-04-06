#include "enemy_behaviour_component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void EnemyBehaviourComponent::init()
{
	playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	entityTr = entity_->getComponent<Transform>();
	enemyDetection = entity_->getComponent<DistanceDetection>();
	assert(playerTr != nullptr && entityTr != nullptr && enemyDetection != nullptr);
}

//--------------------------------------------------------------------------------------------------------------

ChasePlayer::ChasePlayer(float speed_, float stopDistance_) :speed(speed_), stopDistance(stopDistance_){};

void ChasePlayer::update() {
//If enemy can see player
	if (enemyDetection->isActive()) {
		//If it is further from player than it wants to be
		if (std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()) > stopDistance) {
			//If it is on player's left
			if (playerTr->getPos().getX() - entityTr->getPos().getX() > 0.0f)
				entityTr->setVelX(speed);
			//If it is on player's right
			else if (playerTr->getPos().getX() - entityTr->getPos().getX() < 0.0f)
				entityTr->setVelX(-speed);
		}
		else entityTr->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

KeepDistance::KeepDistance(float speed_, float marginDistance_, float shootDistance_) : speed(speed_), 
marginDistance(marginDistance_), shootDistance(shootDistance_) {
	assert(marginDistance < shootDistance);
};

void KeepDistance::update() {
	if (enemyDetection->isActive()) {
		float distance = playerTr->getPos().getX() - entityTr->getPos().getX();

		if (std::abs(distance) < marginDistance) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) entityTr->setVelX(-speed);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) entityTr->setVelX(speed);
		}
		else if (std::abs(distance) > shootDistance) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) entityTr->setVelX(speed);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) entityTr->setVelX(-speed);
		}
		else entityTr->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

FlyingChasePlayer::FlyingChasePlayer(float speed_, float stopDistance_, float hoverHeight_, float attackDistance_) :
	speed(speed_), stopDistance(stopDistance_), hoverHeight(hoverHeight_), attackDistance(attackDistance_) {};

void FlyingChasePlayer::update() {
	//If enemy can see player
	if (enemyDetection->isActive()) {
		//If it is further from player than it wants to be
		if (std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()) > stopDistance) {
			float targetX = playerTr->getPos().getX(), targetY = 0.0;
			//If it is too far to begin attacking, it will keep its altitude
			if (std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()) > attackDistance)
				targetY = hoverHeight;
			else
				targetY = playerTr->getPos().getY();
			
			Point2D target = Point2D(targetX, targetY);
			entityTr->setVel(target - entityTr->getPos());
		}
		else entityTr->setVelX(0.0);
	}
}
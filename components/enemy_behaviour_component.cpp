#include "enemy_behaviour_component.h"

#include "Transform.h"
#include "rigid_body.h"

void EnemyBehaviourComponent::init()
{
	playerTr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	tr_ = entity_->getComponent<Transform>();
	rb_ = entity_->getComponent<RigidBody>();
	enemyDetection = entity_->getComponent<DistanceDetection>();
	assert(playerTr_ != nullptr && tr_ != nullptr && enemyDetection != nullptr);
}

//--------------------------------------------------------------------------------------------------------------

ChasePlayer::ChasePlayer(float speed_, float stopDistance_) :speed(speed_), stopDistance(stopDistance_){};

void ChasePlayer::update() {
//If enemy can see player
	if (enemyDetection->isActive()) {
		//If it is further from player than it wants to be
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > stopDistance) {
			//If it is on player's left
			if (playerTr_->getPos().getX() - tr_->getPos().getX() > 0.0f)
				rb_->setVelX(speed);
			//If it is on player's right
			else if (playerTr_->getPos().getX() - tr_->getPos().getX() < 0.0f)
				rb_->setVelX(-speed);
		}
		else rb_->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

KeepDistance::KeepDistance(float speed_, float marginDistance_, float shootDistance_) : speed(speed_), 
marginDistance(marginDistance_), shootDistance(shootDistance_) {
	assert(marginDistance < shootDistance);
};

void KeepDistance::update() {
	if (enemyDetection->isActive()) {
		float distance = playerTr_->getPos().getX() - tr_->getPos().getX();

		if (std::abs(distance) < marginDistance) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) rb_->setVelX(-speed);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) rb_->setVelX(speed);
		}
		else if (std::abs(distance) > shootDistance) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) rb_->setVelX(speed);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) rb_->setVelX(-speed);
		}
		else rb_->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

FlyingChasePlayer::FlyingChasePlayer(float speed_, float stopDistance_, float hoverHeight_, float attackDistance_) :
	speed(speed_), stopDistance(stopDistance_), hoverHeight(hoverHeight_), attackDistance(attackDistance_) {};

void FlyingChasePlayer::update() {
	//If enemy can see player
	if (enemyDetection->isActive()) {
		//If it is further from player than it wants to be
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > stopDistance) {
			float targetX = playerTr_->getPos().getX(), targetY = 0.0;

			//Get current height
			RayCast distanceToFloor = RayCast(tr_->getPos(), Vector2D(0.0, 1.0));
			distanceToFloor.distanceToGroup<Wall_grp>(entity_);
			Point2D floorPoint = distanceToFloor.getPointOfImpact();

			//If it is too far to begin attacking, it will attempt to maintain its hoverHeight
			if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > attackDistance)
				targetY = floorPoint.getY() - hoverHeight;
			else
				targetY = playerTr_->getPos().getY();

			Point2D target = Point2D(targetX, targetY);
			//Set speed to travel towards target
			rb_->setVel(target - tr_->getPos());
		}
		else rb_->setVel(Vector2D());
	}
}
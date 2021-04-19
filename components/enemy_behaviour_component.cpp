#include "enemy_behaviour_component.h"
#include "Transform.h"
#include "rigid_body.h"
#include "enemy_attack_component.h"
#include "../../sdlutils/SDLUtils.h"

void EnemyBehaviourComponent::update()
{
	if (attack_ != nullptr && (playerTr_->getPos() - tr_->getPos()).magnitude() < attackDistance_ && 
		sdlutils().currRealTime() - lastAttack_ >= attackCooldown_)
		if(attack_->attack())
			lastAttack_ = sdlutils().currRealTime();
}

void EnemyBehaviourComponent::init()
{
	playerTr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	tr_ = entity_->getComponent<Transform>();
	rb_ = entity_->getComponent<RigidBody>();
	enemyDetection_ = entity_->getComponent<DistanceDetection>();
	attack_ = entity_->getComponent<EnemyAttackComponent>();
	assert(playerTr_ != nullptr && tr_ != nullptr && enemyDetection_ != nullptr && attack_ != nullptr);
}

//--------------------------------------------------------------------------------------------------------------

ChasePlayer::ChasePlayer(float speed, float attackDistance) :EnemyBehaviourComponent(speed, attackDistance){};

void ChasePlayer::update() {
//If enemy can see player
	if (enemyDetection_->isActive()) {
		//If it is further from player than it wants to be and is moving slower than its speed
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > attackDistance_ &&
			rb_->getVel().magnitude() < speed_) {

			//If it is on player's left
			if (playerTr_->getPos().getX() - tr_->getPos().getX() > 0.0f)
				rb_->setVelX(speed_);
			//If it is on player's right
			else if (playerTr_->getPos().getX() - tr_->getPos().getX() < 0.0f)
				rb_->setVelX(-speed_);
		}
		else if (rb_->getVel().magnitude() < speed_)
			rb_->setVel(rb_->getVel() * 0.95);
		else rb_->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

KeepDistance::KeepDistance(float speed, float marginDistance, float attackDistance) : 
	EnemyBehaviourComponent(speed, attackDistance), marginDistance_(marginDistance_) {
	assert(marginDistance_ < attackDistance_);
};

void KeepDistance::update() {
	if (enemyDetection_->isActive()) {
		float distance = playerTr_->getPos().getX() - tr_->getPos().getX();

		if (std::abs(distance) < marginDistance_) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) rb_->setVelX(-speed_);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) rb_->setVelX(speed_);
		}
		else if (std::abs(distance) > attackDistance_) {
			//Enemigo a la izquierda del jugador
			if (distance > 0.0f) rb_->setVelX(speed_);

			//Enemigo a la derecha del jugador
			else if (distance < 0.0f) rb_->setVelX(-speed_);
		}
		else rb_->setVelX(0.0);
	}
}

//--------------------------------------------------------------------------------------------------------------

FlyingChasePlayer::FlyingChasePlayer(float speed, float attackDistance, float hoverHeight, float approachDistance) :
	EnemyBehaviourComponent(speed, attackDistance), hoverHeight_(hoverHeight), approachDistance_(approachDistance) { };

void FlyingChasePlayer::update() {
	this->EnemyBehaviourComponent::update();
	Vector2D target = tr_->getPos();
	//If it can detect the player
	if (enemyDetection_->isActive())
	{
		// Approach player horizontally
			target.setX(playerTr_->getPos().getX());

		//If it is too far to begin attacking, it will attempt to maintain its hoverHeight
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > approachDistance_)
		{
			//Get point of floor directly below 
			RayCast distanceToFloor = RayCast(tr_->getPos(), Vector2D(0.0, 1.0));
			distanceToFloor.distanceToGroup<Wall_grp>(entity_->getMngr());
			Point2D floorPoint = distanceToFloor.getPointOfImpact();

			target.setY(floorPoint.getY() - hoverHeight_);			
		}
		// If it is within attack range, it will home in on the player vertically as well
		else
			target.setY(playerTr_->getPos().getY() - 50.0);

		// Set speed to travel towards target
		if (rb_->getVel().magnitude() < speed_ + 0.1)
			rb_->setVel((target - tr_->getPos()).normalize() * speed_);
		// If it is being knocked back or is mid-lunge, it will decelerate
		else if (rb_->getVel().magnitude() > 0.01)
			rb_->setVel(rb_->getVel() * 0.95);
	}
	else
		rb_->setVel(Vector2D());
}
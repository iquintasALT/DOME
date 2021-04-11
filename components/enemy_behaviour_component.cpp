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

FlyingChasePlayer::FlyingChasePlayer(float speed, float stopDistance, float hoverHeight, float attackDistance) :
	speed_(speed), stopDistance_(stopDistance), hoverHeight_(hoverHeight), attackDistance_(attackDistance) 
{
	//rb_->setGravity(0.0f);
};

void FlyingChasePlayer::update() {
	Vector2D target = tr_->getPos();
	//If it can detect the player and is further from player than it wants to be
	if (enemyDetection->isActive() && (playerTr_->getPos() - tr_->getPos()).magnitude() > stopDistance_)
	{
		//If it is further from player than it wants to be, it will approach player horizontally
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > stopDistance_) {
			target.setX(playerTr_->getPos().getX());
		}

		//If it is too far to begin attacking, it will attempt to maintain its hoverHeight
		if (std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) > attackDistance_)
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

		//Set speed to travel towards target
		rb_->setVel((target - tr_->getPos()).normalize() * speed_);
		/*cout << "Player position: " << playerTr_->getPos().getX() << ", " << playerTr_->getPos().getY() 
			<< "      Target: " << target.getX() << ", " << target.getY() << endl;*/
	}
	else
		rb_->setVel(Vector2D());
}
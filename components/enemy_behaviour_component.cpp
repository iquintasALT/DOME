#include "enemy_behaviour_component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"

void EnemyBehaviourComponent::init()
{
	playerTr = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	entityTr = entity_->getComponent<Transform>();
}

ChasePlayer::ChasePlayer(float speed_) { speed = speed_; };

void ChasePlayer::update()
{
	if (std::abs(playerTr->getPos().getX() - entityTr->getPos().getX()) > 50)
	{
		if (playerTr->getPos().getX() - entityTr->getPos().getX() > 50)
			entityTr->setVelX(speed);
		else if (playerTr->getPos().getX() - entityTr->getPos().getX() < -50)
			entityTr->setVelX(-speed);
	}
	else
		entityTr->setVelX(0.0);
}

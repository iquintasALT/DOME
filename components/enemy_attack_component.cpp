#include "enemy_attack_component.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/ray_cast.h"

Vector2D EnemyAttackComponent::getTarget()
{
	return playerTr_->getPos() - tr_->getPos();
}

void EnemyAttackComponent::init()
{
	tr_ = entity_->getComponent<Transform>();
	playerTr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
}
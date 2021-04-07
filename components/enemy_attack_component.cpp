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

//--------------------------------------------------------------------------------------------------------------

bool GroundedMeleeAttack::attack()
{
	// Only attacks if grounded
	if (RayCast::isGrounded(tr_))
	{
		/// Set length of jump to maximum length at most, or less, if closer to player than leap permits
		/// For y component, the max function is used to ensure that downward jumps don't occur
		Vector2D jump = Vector2D(std::min(lunge.getX(), std::abs(playerTr_->getPos().getX() - tr_->getPos().getX())),
			-std::min(lunge.getY(), std::max(tr_->getPos().getY() - playerTr_->getPos().getY(), 0.0f)));

		//Ensure that jump is in correct direction
		if (tr_->getPos().getX() > playerTr_->getPos().getX())
			jump.setX(-jump.getX());

		return true;
	}
	else return false;
}
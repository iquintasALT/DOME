#include "enemy_attack_component.h"
#include "Transform.h"
#include "classic_bullet.h"
#include "Image.h"
#include "enemy_animation.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/ray_cast.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"


Vector2D EnemyAttackComponent::getTarget()
{
	return playerTr_->getPos() - tr_->getPos();
}

void EnemyAttackComponent::init()
{
	tr_ = entity_->getComponent<Transform>();
	playerTr_ = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>();
	rb_ = entity_->getComponent<RigidBody>();
}

//--------------------------------------------------------------------------------------------------------------

bool MeleeAttack::attack()
{
	// Set length of jump to maximum length at most, or less, if closer to player than leap permits
	Vector2D jump = Vector2D(std::min(lunge.getX(), std::abs(playerTr_->getPos().getX() - tr_->getPos().getX())),
		-std::min(lunge.getY(), std::abs(playerTr_->getPos().getY() - tr_->getPos().getY())));

	// Ensure that boost is in correct direction
	if (tr_->getPos().getX() > playerTr_->getPos().getX())
		jump.setX(-jump.getX());
	if (tr_->getPos().getY() < playerTr_->getPos().getY())
		jump.setY(-jump.getY());

	rb_->setVel(jump);

	return true;
}

//--------------------------------------------------------------------------------------------------------------

void GroundedMeleeAttack::init()
{
	MeleeAttack::init();
	animator = entity_->getComponent<EnemyAnimation>();
}

bool GroundedMeleeAttack::attack()
{
	// Only attacks if grounded
	if (RayCast::isGrounded(tr_))
	{
		/// Set length of jump to maximum length at most, or less, if closer to player than leap permits
		/// For y component, the max function is used to ensure that downward jumps don't occur
		Vector2D jump = Vector2D();
		jump.setX(std::min(lunge.getX(), std::abs(playerTr_->getPos().getX() - tr_->getPos().getX()) + lunge.getX() / 2));

		jump.setY(-std::min(lunge.getY(), std::max(tr_->getPos().getY() - playerTr_->getPos().getY() + lunge.getY() / 2, 0.0f)));

		// Ensure that jump is in correct direction
		if (tr_->getPos().getX() > playerTr_->getPos().getX())
			jump.setX(-jump.getX());

		// Apply jump boost
		rb_->setVel(rb_->getVel() + jump);

		soundManager().playSFX("monster1attack");
		return true;
	}
	else return false;
}
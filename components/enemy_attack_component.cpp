#include "enemy_attack_component.h"
#include "Transform.h"
#include "classic_bullet.h"
#include "Image.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/ray_cast.h"
#include "../../sdlutils/SDLUtils.h"

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

bool GroundedMeleeAttack::attack()
{
	// Only attacks if grounded
	if (RayCast::isGrounded(tr_))
	{
		/// Set length of jump to maximum length at most, or less, if closer to player than leap permits
		/// For y component, the max function is used to ensure that downward jumps don't occur
		Vector2D jump = Vector2D(std::min(lunge.getX(), std::abs(playerTr_->getPos().getX() - tr_->getPos().getX())),
			-std::min(lunge.getY(), std::max(tr_->getPos().getY() - playerTr_->getPos().getY(), 0.0f)));

		// Ensure that jump is in correct direction
		if (tr_->getPos().getX() > playerTr_->getPos().getX())
			jump.setX(-jump.getX());

		return true;
	}
	else return false;
}

//--------------------------------------------------------------------------------------------------------------

bool RangedAttack::attack()
{
	RayCast rC = RayCast(tr_->getPos(), playerTr_);
	if (rC.getDistance() < range_)
	{
		/// TO DO
		/// fire a bullet
		Entity* bullet = entity_->getMngr()->addEntity();
		Transform* bulletTr = bullet->addComponent<Transform>(Vector2D(tr_->getPos()), 4, 6, 0);
		RigidBody* rb = bullet->addComponent<RigidBody>((playerTr_->getPos() - tr_->getPos()) * 10.0, false);


		entity_->getMngr()->addRenderLayer<Bullets>(bullet);
		entity_->setGroup<Enemy_grp>(true);
		bullet->addComponent<Image>(&sdlutils().images().at("projectile"));
		bullet->addComponent<ClassicBullet>();

		return true;
	}
	else return false;
}
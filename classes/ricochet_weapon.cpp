#include "ricochet_weapon.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../classes/camera.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/constant_variables.h"
#include "../components/ricochet.h"
#include "../game/constant_variables.h"

#include "../classes/Item.h"

int RicochetWeapon::bulletsInMagazine = 0;

Entity* RicochetWeapon::createBullet(const Vector2D& direction){
	Entity* bullet = entity_->getMngr()->addEntity();
	bullet->addComponent<Transform>(Vector2D(), 4, 6, 0);
	bullet->addComponent<RigidBody>(direction * 10.0, true);
	bullet->addComponent<Image>(bulletTexture_);
	bullet->addComponent<Ricochet>(playerTr_, nbounce, ntier);
	entity_->getMngr()->addRenderLayer<Bullets>(bullet);

	return bullet;
}

void RicochetWeapon::init()
{
	Weapon::init();
	bulletTexture_ = &sdlutils().images().at("ricochet_projectile");
}

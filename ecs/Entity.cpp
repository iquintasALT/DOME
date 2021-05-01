#include "Entity.h"
#include "Manager.h"

void Entity::removeEntityRender(Entity* ent, Manager* mngr_) {

	mngr_->removeRender(ent);
}
#include "Entity.h"
#include "Manager.h"

void Entity::removeEntityRender(Entity* ent) {
	mngr_->removeRenderFromLayer(ent);
}
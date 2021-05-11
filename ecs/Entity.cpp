#include "Entity.h"
#include "Manager.h"

void Entity::removeEntityRender() {

	mngr_->removeRenderFromLayer(this);
}
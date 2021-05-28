#include "parallax_component.h"

#include "../ecs/Entity.h"
#include "../components/transform.h"
#include "../classes/camera.h"

void ParallaxComponent::init() {
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);
}

void ParallaxComponent::render() {
	Vector2D pos = Camera::mainCamera->renderRect(tr->getPos());
	if (scrollFactor < 1) {
		pos.setY(tr->getPos().getY());
		pos.setX(pos.getX() * scrollFactor);
	}
	float scale = Camera::mainCamera->getScale();

	SDL_Rect dest = build_sdlrect(pos, tr->getW(), tr->getH());
	dest.x *= scale; dest.y *= scale;
	dest.w *= scale; dest.h *= scale;

	for (int i = 0; i < numOfRepetitions; i++) {
		SDL_Rect nextDest = dest; nextDest.x += i * tr->getW();
		text->render(src_, nextDest, tr->getRot(), nullptr, SDL_FLIP_NONE);
	}
}

void ParallaxComponent::setScrollFactor(float value) {
	if (value < 0) value = 0;
	else if (value > 1) value = 1;
	scrollFactor = value;
}

#include "CameraMovement.h"
#include "../game/constant_variables.h"

void CameraMovement::init() {
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);
}

void CameraMovement::update() {
	if (player == nullptr) return;

	auto& pos = tr->getPos();
	pos = Vector2D::Lerp(pos, player->getPos(), 0.7f * consts::DELTA_TIME);
}
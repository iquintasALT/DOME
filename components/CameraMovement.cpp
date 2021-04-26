#include "CameraMovement.h"

CameraMovement::CameraMovement(float _vel) {
	velocity = _vel;
	tr = nullptr;
	cam = nullptr;
}

void CameraMovement::init() {
	tr = entity_->getComponent<Transform>();
	cam = Camera::mainCamera;
	assert(tr != nullptr && cam != nullptr);
}

void CameraMovement::update() {
	cam->LerpWithBounds(tr->getPos(), velocity);
}


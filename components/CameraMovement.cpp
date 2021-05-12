#include "CameraMovement.h"
#include "../components/rigid_body.h"
#include "../game/constant_variables.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"

CameraMovement::CameraMovement(float _vel) {
	velocity = _vel;
	tr = nullptr;
	cam = nullptr;
	rb = nullptr;
}


void CameraMovement::init() {
	tr = entity_->getComponent<Transform>();
	rb = entity_->getComponent<RigidBody>();
	cam = Camera::mainCamera;
	assert(tr != nullptr && cam != nullptr);

	cam->Move(tr->getPos());

}

void CameraMovement::update() {

	Vector2D pos = tr->getPos();
	if (rb != nullptr && rb->onFloor()) {
		pos = pos + Vector2D(0, consts::CAMERA_MARGIN_FROM_PLAYER);
	}

	int x = rb->getVel().getX();
	int dir = (x > 0) - (x < 0);
	pos = pos + Vector2D(consts::PLAYER_SPEED, 0) * dir * consts::WINDOW_WIDTH / 5;
	cam->LerpWithBounds(pos, velocity);
}


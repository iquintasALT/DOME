#include "InitialCameraZoom.h"
#include "../classes/camera.h"
#include "../ecs/Entity.h"
#include "../game/constant_variables.h"
InitialCameraZoom::InitialCameraZoom(float zoom, float time):
	 totalTime(time)
{
	t = 0;
	initialZoom = Camera::mainCamera->getScale();
	targetZoom = initialZoom * zoom;
}

void InitialCameraZoom::update()
{
	t += consts::DELTA_TIME;

	if (t > totalTime) {
		Camera::mainCamera->setScale(targetZoom);
		entity_->setDead(true);
		return;
	}

	float scale = Vector2D::Lerp(initialZoom, targetZoom, t / totalTime);
	Camera::mainCamera->setScale(scale);
}

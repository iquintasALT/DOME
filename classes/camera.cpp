#include "camera.h"
#include <iostream>

Camera* Camera::mainCamera = nullptr;

Camera::Camera(Vector2D&& initial, int cam_w, int cam_h) {
	pos = std::move(initial);
	width = cam_w;
	height = cam_h;
}

void Camera::setMain(Camera* cam) {
	if (mainCamera != nullptr)
		delete mainCamera;
	mainCamera = cam;
}

void Camera::Move(Vector2D& newPos) {
	pos = newPos;
}

void Camera::MoveDir(Vector2D dir) {
	pos = pos + dir;
}

void Camera::FollowPlayer(Vector2D& playerPos) {
	pos = playerPos + Vector2D(-width / 2, -height / 4 * 3);
}


Vector2D Camera::renderRect(Vector2D& imagePos,int w, int h, bool& shouldRender) {
	if (!(imagePos.getX() + width > pos.getX() && 
		imagePos.getX() < pos.getX() + width &&
		imagePos.getY() + height > pos.getY() && 
		imagePos.getY() < pos.getY() + height))
	{
		shouldRender = false;
		return Vector2D();
	}

	return Vector2D(imagePos.getX() - pos.getX(), imagePos.getY() - pos.getY());
}
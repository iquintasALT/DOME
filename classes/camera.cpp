#include "camera.h"
#include <iostream>
#include "../game/constant_variables.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera(Vector2D&& initial, int cam_w, int cam_h) {
	pos = std::move(initial);
	width = cam_w;
	height = cam_h;

	xmin = ymin = xmax = ymax = 0;
}

void Camera::setMain(Camera* cam) {
	if (mainCamera != nullptr)
		delete mainCamera;
	mainCamera = cam;
}

void Camera::Move(Vector2D& newPos) {
	pos = newPos;
}

void Camera::Lerp(const Vector2D& newPos) {
	if ((pos - newPos).magnitude() > 2)
		pos = Vector2D::Lerp(pos, newPos - Vector2D(width / 2, height / 2), 0.7f * consts::DELTA_TIME);
}
void Camera::LerpWithBounds(const Vector2D& newPos) {
	Lerp(newPos);

	Vector2D& p = pos;
	if (p.getX() < xmin) p.setX(xmin);
	else if (p.getX() > xmax) p.setX(xmax);

	if (p.getY() < ymin) p.setY(ymin);
	else if (p.getY() > ymax) p.setY(ymax);
}

void Camera::setBounds(float a, float b, float c, float d) {
	xmin = a;
	ymin = b;
	xmax = c;
	ymax = d;
}

void Camera::MoveDir(Vector2D dir) {
	pos = pos + dir;
}

void Camera::FollowPlayer(Vector2D& playerPos) {
	pos = playerPos + Vector2D(-width / 2, -height / 4 * 3);
}


Vector2D Camera::renderRect(Vector2D& imagePos, int w, int h, bool& shouldRender) {
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


Point2D Camera::PointToWorldSpace(Point2D& point) {
	return point + pos;
}
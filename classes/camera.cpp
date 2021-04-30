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

void Camera::Lerp(const Vector2D& newPos, float i) {
	Vector2D newcamerapos = newPos - Vector2D(width / 2, height / 2);

	if ((pos - newcamerapos).magnitude() > 2)
		pos = Vector2D::Lerp(pos, newcamerapos, i * consts::DELTA_TIME);
}
void Camera::LerpWithBounds(const Vector2D& newPos, float i) {
	Lerp(newPos, i);

	Vector2D& p = pos;
	if (p.getX() < xmin) p.setX(xmin);
	else if (p.getX() > xmax) p.setX(xmax);

	if (p.getY() < ymin) p.setY(ymin);
	else if (p.getY() > ymax) p.setY(ymax);
}

void Camera::setBounds(float a, float b, float c, float d) {
	xmin = a;
	ymin = b;
	xmax = c - width;
	ymax = d - height;
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


Point2D Camera::PointToWorldSpace(Point2D point) {
	return point + pos;
}

Point2D Camera::WorldToPointSpace(Point2D point) {
	return point - pos;
}

bool Camera::isVisible(Point2D point) {
	return
		point.getX() >= pos.getX() &&
		point.getX() < pos.getX() + width &&
		point.getY() >= pos.getY() &&
		point.getY() < pos.getY() + height;
}
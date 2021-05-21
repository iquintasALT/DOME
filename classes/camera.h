#pragma once
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"

class Camera
{
private:
	Vector2D pos;
	int width, height;
	int winWidth, winHeight;

	float scale;
	float xmin, ymin, xmax, ymax;

public:
	static Camera* mainCamera;
	
	Camera(Vector2D&& initialPos, int cam_w, int cam_h);
	static void setMain(Camera* cam);
	void Move(Vector2D& v);
	void MoveToPoint(Vector2D& v);
	void Lerp(const Vector2D& v, float i);
	void LerpWithBounds(const Vector2D& v, float i);
	void setBounds(float xmin, float ymin, float xmax, float ymax);
	void FollowPlayer(Vector2D& pos);
	Vector2D renderRect(Vector2D& imagePos,int w, int h, bool& shouldRender);
	Vector2D renderRect(Vector2D& imagePos);
	void MoveDir(Vector2D dir);
	void setScale(float value);
	float getScale();
	Point2D PointToWorldSpace(Point2D point);
	Point2D WorldToPointSpace(Point2D point);
	Point2D getCameraPosition();
	bool isVisible(Point2D point);
};


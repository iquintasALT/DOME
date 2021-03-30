#pragma once
#include "../utils/Vector2D.h"
#include "../game/checkML.h"

class Camera
{
private:
	Vector2D pos;
	int width, height;

public:
	static Camera* mainCamera;
	
	Camera(Vector2D&& initialPos, int cam_w, int cam_h);
	static void setMain(Camera* cam);
	void Move(Vector2D& v);
	void FollowPlayer(Vector2D& pos);
	Vector2D renderRect(Vector2D& imagePos,int w, int h, bool& shouldRender);
	void MoveDir(Vector2D dir);
	Point2D PointToWorldSpace(Point2D& point);
};


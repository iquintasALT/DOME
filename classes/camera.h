#pragma once
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"

class Camera
{
private:
	Vector2D pos;
	int width, height;
	float xmin, ymin, xmax, ymax;

public:
	static Camera* mainCamera;
	
	Camera(Vector2D&& initialPos, int cam_w, int cam_h);
	static void setMain(Camera* cam);
	void Move(Vector2D& v);
	void Lerp(const Vector2D& v, float i);
	void LerpWithBounds(const Vector2D& v, float i);
	void setBounds(float xmin, float ymin, float xmax, float ymax);
	void FollowPlayer(Vector2D& pos);
	Vector2D renderRect(Vector2D& imagePos,int w, int h, bool& shouldRender);
	void MoveDir(Vector2D dir);
	Point2D PointToWorldSpace(Point2D point);
};


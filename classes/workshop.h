#pragma once
#include "../classes/game_entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Collisions.h"
#include <vector>

class Workshop : public GameEntity
{
private:
	Image* renderImg;
	Vector2D bg_pos;
	Vector2D bg_size;
	std::string bgName;
	Vector2D bButton_pos;
	Vector2D bButton_size;
	std::string bButtonName;

	std::vector<Image*>craftList;
	Transform* tr;

	bool renderFlag;

public:
	Workshop(Manager* mngr_);

	void setImg(Vector2D pos, Vector2D size, std::string name);
	virtual void render();
	virtual void update();
	void setRenderFlag(bool set);
};


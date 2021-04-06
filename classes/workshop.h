#pragma once
#include "../classes/game_entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Collisions.h"
#include <vector>

class Workshop : public GameEntity
{
private:
	Entity* bg;
	Transform* bg_tr;
	Entity* bButton;
	Transform* bButton_tr;

	std::vector<Entity*>craftList;
	Transform* tr;

	bool renderFlag;

public:
	Workshop(Manager* mngr_);

	void setImg(Entity* entity,Vector2D pos, Vector2D size, std::string name);
	virtual void render();
	virtual void update();
	void setRenderFlag(bool set);
};


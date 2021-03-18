#pragma once

#include "../sdlutils/InputHandler.h"
#include "../ecs/Component.h"
#include "../Components/Transform.h"
class Manager;
class Interactions: public Component
{
private:
	Manager* manager;
	Transform* transform;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
public:
	Interactions() : manager(nullptr), transform(nullptr){};
	void update() override;
	void init() override;
};


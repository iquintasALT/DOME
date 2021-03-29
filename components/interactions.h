#pragma once

#include "../sdlutils/InputHandler.h"
#include "../ecs/Component.h"
#include "../Components/Transform.h"
#include "../game/checkML.h"

class Manager;
class Interactions: public Component
{
private:
	Manager* manager;
	Transform* transform;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	bool justPressed;

public:
	Interactions() : manager(nullptr), transform(nullptr) { justPressed = false; };
	void update() override;
	void init() override;
};


#pragma once

#include "../ecs/Component.h"
#include <string>
class TextWithBackground;
class Dialogue: public Component
{
public:
	void init();

	void update();

	void createText(std::string text, float speed);

private:
	TextWithBackground* text;
	Entity* background;
};


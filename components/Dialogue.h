#pragma once

#include "../ecs/Component.h"

#include <string>
#include <vector>
#include <functional>

class TextWithBackground;
class Dialogue : public Component
{
public:
	Dialogue(int height = 200);

	void update();

	void createText(std::string text, float speed);
	void createText(std::vector<std::string> texts, float speed);

	std::function<void()> function;
private:
	TextWithBackground* text;
	Entity* background;

	float textSpeed;

	void showText(std::string txt);
	void showBackground();
	int index;
	int height;
	std::vector<std::string> texts;
};


#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../components/Transform.h"
#include "../sdlutils/Texture.h"

#include <string>
#include <vector>

class TextWithBackground : public Component
{
private:
	Transform* tr_;
	// The picture that the text is rendered on top of
	Texture* texture_;
	// A vector of individual letter images that are currently being rendered
	std::vector<Texture*> text_;
	// The message to be spelt out this frame
	std::string message_;
	// The font to use
	Font* font_;
	// The colour of the text. Muahaha I spelt colour with a u
	SDL_Color col_;

	// Indicates whether the text is currently being unfurled
	bool appearingText_;
	float textSpeed;
	// In the case of an unfurling message, this is the complete text. Otherwise, this is not used
	std::string finalMessage_;
	// The index of the next letter to be rendered
	int currentIndex;

	bool centerAlign;

	void changeTextTextures();
public:
	TextWithBackground(std::string str, Font& font, SDL_Color  color, Texture* texture, bool appearingText = false, float appeatingTextSpeed = 1, bool alignInCenter = false);
	~TextWithBackground();
	void changeText(std::string txt);
	void init() override;
	void render() override;
	void update() override;
	void setAlpha(int value);
	void reset();
};


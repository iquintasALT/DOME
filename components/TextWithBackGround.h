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
	Transform* tr;
	Texture* texture;
	std::vector<Texture*> text;
	std::string message;
	Font* _font;
	SDL_Color _col;
public:
	TextWithBackground(std::string str, Font & font, SDL_Color  color, Texture* texture );
	~TextWithBackground();
	void init() override;
	void render() override;
};


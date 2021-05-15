#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
class Texture;
class Transform;

class ParallaxComponent : public Component
{
private:
	int numOfRepetitions;
	Texture* text;
	Transform* tr;
	float scrollFactor;
	SDL_Rect src_;
public:
	ParallaxComponent(Texture* t, int numOfRep) : numOfRepetitions(numOfRep), text(t), scrollFactor(1), src_({ 0,0,text->width(),text->width() }), tr(nullptr){};
	void init() override;
	void render() override;
	void setScrollFactor(float value);
};


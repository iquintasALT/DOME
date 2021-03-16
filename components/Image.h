// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../game/checkML.h"

#include "Transform.h"

class Image : public Component {
public:
	Image(Texture* tex) :
		tr_(nullptr), //
		tex_(tex), //
		src_({ 0,0,tex->width(),tex->width() }),
		flip_(SDL_FLIP_NONE),
		rotationOrigin({ -1, -1 })
	{
	}

	Image(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tex_(tex), //
		src_(src),
		flip_(SDL_FLIP_NONE),
		rotationOrigin({ -1, -1 })
	{
	}

	Image(Texture* tex, int rows, int cols, int r, int c) :
		tr_(nullptr), //
		tex_(tex), //
		flip_(SDL_FLIP_NONE),
		rotationOrigin({ -1, -1 })
	{
		int w = tex->width() / cols;
		int h = tex->height() / rows;
		src_ = { w * c ,h * r,w,h };
	}

	virtual ~Image() {
	}

	virtual void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		if (rotationOrigin.x == -1 && rotationOrigin.y == -1)
			tex_->render(src_, dest, tr_->getRot(), nullptr, flip_);
		else {
			tex_->render(src_, dest, tr_->getRot(), &rotationOrigin, flip_);
		}
	}

	inline SDL_Rect& getSrc() {
		return src_;
	}

	inline Texture* getText() {
		return tex_;
	}

	void setSrc(SDL_Rect rect) {
		src_ = rect;
	}

	void setFlip(SDL_RendererFlip flip) {
		flip_ = flip;
	}

	void setRotationOrigin(int x, int y) {
		rotationOrigin = { x, y };
	}

	SDL_Point getOrigin() {
		return rotationOrigin;
	}

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	SDL_RendererFlip flip_;
	SDL_Point rotationOrigin;
};


// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"
#include "../classes/camera.h";
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "Transform.h"

class Image : public Component {
public:
	Image(Texture* tex, bool isUI_ = false) : tr_(nullptr), scrollFactor(1), tex_(tex), src_({ 0,0,tex->width(),tex->width() }),
		flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(isUI_), alpha_(255) {}

	Image(Texture* tex, SDL_Rect src, bool isUI_ = false) : tr_(nullptr), tex_(tex), scrollFactor(1), src_(src),
		flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(isUI_), alpha_(255) {}

	Image(Texture* tex, int rows, int cols, int r, int c, bool isUI_ = false) : tr_(nullptr), tex_(tex), scrollFactor(1),
		flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(isUI_), alpha_(255)
	{
		int w = tex->width() / cols;
		int h = tex->height() / rows;
		src_ = { w * c ,h * r, w, h };
	}

	virtual ~Image() {}

	virtual void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		bool shouldRender = true;
		Vector2D pos = !isUI ? Camera::mainCamera->renderRect(tr_->getPos(), tr_->getW(), tr_->getH(), shouldRender) : tr_->getPos();
		if (scrollFactor < 1) {
			pos.setY(tr_->getPos().getY());
			pos.setX(pos.getX() * scrollFactor);
		}
		float scale = Camera::mainCamera->getScale();
		if (!shouldRender) return;

		SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());
		if (!isUI) {
			dest.x = floor(dest.x * scale);
			dest.y = floor(dest.y * scale);
			dest.w = ceil(dest.w * scale);
			dest.h = ceil(dest.h * scale);
		}

		// en caso de que esta imagen tenga algun tipo de alpha menor a 255
		if (alpha_ < 255)
			tex_->setAlpha(alpha_);

		SDL_Point rot = rotationOrigin;
		rot.x = round(rot.x * scale);
		rot.y = round(rot.y * scale);
		if (rotationOrigin.x == -1 && rotationOrigin.y == -1)
			tex_->render(src_, dest, tr_->getRot(), nullptr, flip_);
		else
			tex_->render(src_, dest, tr_->getRot(), &rot, flip_);

		// en caso de que esta imagen tenga algun tipo de alpha menor a 255
		if (alpha_ < 255)
			tex_->setAlpha(255);
	}

	// util por si queremos hacer algun tipo de pequeña animacion en cosas como tooltips o interfaces
	inline void changeFrame(int newC, int newR) {
		src_ = { newC * src_.w, newR * src_.h, src_.w, src_.h };
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

	inline SDL_RendererFlip getFlip() {
		return flip_;
	}

	void setRotationOrigin(int x, int y) {
		rotationOrigin = { x, y };
	}

	void setAlpha(Uint8 alpha) {
		alpha_ = alpha;
	}

	//Value between 0-1
	void setScrollFactor(float value) {
		if (value < 0) value = 0;
		else if (value > 1) value = 1;
		scrollFactor = value;
	}

	SDL_Point getOrigin() {
		return rotationOrigin;
	}

private:
	Transform* tr_;
	Texture* tex_;

	bool isUI;
	float scrollFactor;
	std::size_t alpha_ = 255;

	SDL_Rect src_;
	SDL_Point rotationOrigin;
	SDL_RendererFlip flip_;
};



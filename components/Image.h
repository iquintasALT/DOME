// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"
#include "../classes/camera.h";
#include "Transform.h"

class Image : public Component {
public:
	Image(Texture* tex) : tr_(nullptr), tex_(tex), src_({ 0,0,tex->width(),tex->width() }),
		flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(false) {}

	Image(Texture* tex, SDL_Rect src) : tr_(nullptr), tex_(tex), src_(src),
		flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(false) {}

	Image(Texture* tex, int rows, int cols, int r, int c, bool isUI = false) : tr_(nullptr), tex_(tex), flip_(SDL_FLIP_NONE), rotationOrigin({ -1, -1 }), isUI(isUI)
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

		if (!shouldRender) return;

		SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());
		if (rotationOrigin.x == -1 && rotationOrigin.y == -1)
			tex_->render(src_, dest, tr_->getRot(), nullptr, flip_);
		else
			tex_->render(src_, dest, tr_->getRot(), &rotationOrigin, flip_);
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
		tex_->setAlpha(alpha);
	}

	SDL_Point getOrigin() {
		return rotationOrigin;
	}

private:
	bool isUI;
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	SDL_RendererFlip flip_;
	SDL_Point rotationOrigin;
};


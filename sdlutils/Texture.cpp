// This file is part of the course TPV2@UCM - Samir Genaim

#include "Texture.h"


Texture& Texture::operator=(Texture &&other) noexcept {
	this->~Texture();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	return *this;
}

Texture::Texture(Texture &&other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName) {
	assert(renderer != nullptr);

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't load image: " + fileName;
	}

	width_ = surface->w;
	height_ = surface->h;
	renderer_ = renderer;
}

void Texture::setColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture_, r, g, b);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture_, alpha);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

Texture::Texture(SDL_Renderer* rend, SDL_Texture* tex, int width, int height)
{
	renderer_ = rend;
	texture_ = tex;
	width_ = width;
	height_ = height;
}

void Texture::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const SDL_Color *bgColor) {
	assert(renderer != nullptr);

	SDL_Surface* surface_ = bgColor == nullptr ?
			   font.renderText(text, *fgColor) :
			   font.renderText(text, *fgColor, *bgColor);

	if (surface_ == nullptr)
		throw "Couldn't create text: " + text;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface_);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface_);
		throw "Couldn't create text: " + text;
	}

	width_ = surface_->w;
	height_ = surface_->h;
	renderer_ = renderer;

}

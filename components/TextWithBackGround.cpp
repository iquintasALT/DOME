#include "TextWithBackGround.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../utils/checkML.h"

TextWithBackground::TextWithBackground(std::string msg, Font& font, SDL_Color col, Texture* tex, bool appearingText) {
	tr_ = nullptr;
	texture_ = tex;
	message_ = msg;
	font_ = &font;
	col_ = col;
	appearingText_ = appearingText;
	currentIndex = 0;
}

void TextWithBackground::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);

	if (appearingText_) {
		finalMessage_ = message_;
		message_ = "";
	}
	else
		changeTextTextures();
}

void TextWithBackground::render() {
	float y = 0;
	for (int i = 0; i < text_.size(); i++)
		y += text_[i]->height();

	if (texture_ != nullptr) {
		SDL_Rect pos{ tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), y };
		texture_->render(pos);
	}

	SDL_Rect textPos{ tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), 10 };
	for (int i = 0; i < text_.size(); i++) {
		textPos.h = text_[i]->height();
		textPos.w = text_[i]->width();
		text_[i]->render(textPos);
		textPos.y += text_[i]->height();
	}
}

void TextWithBackground::changeTextTextures() {
	for (int i = 0; i < text_.size(); i++)
		delete text_[i];
	text_.clear();

	Texture* t = nullptr;
	std::string str = message_;
	std::string second = "";
	auto renderer = sdlutils().renderer();

	bool added;
	do {
		second = "";
		bool completed = false;
		added = false;
		do {
			t = new Texture(renderer, str, *font_, col_);

			completed = t->width() > tr_->getW();

			if (completed && str.size() > 0) {
				second = str[str.size() - 1] + second;
				str.pop_back();
				added = true;
				delete t;
				t = nullptr;
			}

			if (second.size() > 0 && second[second.size() - 1] == ' ')
				second.pop_back();

			if (t != nullptr)
				text_.push_back(t);
		} while (completed && str.size() > 0);
		str = second;
	} while (added);
}

void TextWithBackground::changeText(std::string txt) {
	message_ = txt;
	changeTextTextures();
}
TextWithBackground::~TextWithBackground() {
	for (auto a : text_) {
		delete a;
	}
	text_.clear();
}

float t = 0;
void TextWithBackground::update() {
	if (!appearingText_) return;

	t += consts::DELTA_TIME;
	if (t > .1f) {
		t = 0;
		message_ += finalMessage_[currentIndex++];
		changeTextTextures();

		if (currentIndex >= finalMessage_.size())
			appearingText_ = false;
	}
}

void TextWithBackground::setAlpha(int value) {
	texture_->setAlpha(value);
}

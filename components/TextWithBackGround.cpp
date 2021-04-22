#include "TextWithBackGround.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../utils/checkML.h"

TextWithBackground::TextWithBackground(std::string msg, Font& font, SDL_Color col, Texture* tex, bool appearingText) {
	tr = nullptr;
	texture = tex;
	message = msg;
	_font = &font;
	_col = col;
	_appearingText = appearingText;
	currentIndex = 0;
}

void TextWithBackground::init() {
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);

	if (_appearingText) {
		finalMessage = message;
		message = "";
	}
	else
		changeTextTextures();
}

void TextWithBackground::render() {
	float y = 0;
	for (int i = 0; i < text.size(); i++)
		y += text[i]->height();

	if (texture != nullptr) {
		SDL_Rect pos{ tr->getPos().getX(), tr->getPos().getY(), tr->getW(), y };
		texture->render(pos);
	}

	SDL_Rect textPos{ tr->getPos().getX(), tr->getPos().getY(), tr->getW(), 10 };
	for (int i = 0; i < text.size(); i++) {
		textPos.h = text[i]->height();
		textPos.w = text[i]->width();
		text[i]->render(textPos);
		textPos.y += text[i]->height();
	}
}

void TextWithBackground::changeTextTextures() {
	for (int i = 0; i < text.size(); i++)
		delete text[i];
	text.clear();

	Texture* t = nullptr;
	std::string str = message;
	std::string second = "";
	auto renderer = sdlutils().renderer();

	bool added;
	do {
		second = "";
		bool completed = false;
		added = false;
		do {
			t = new Texture(renderer, str, *_font, _col);

			completed = t->width() > tr->getW();

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
				text.push_back(t);
		} while (completed && str.size() > 0);
		str = second;
	} while (added);
}

void TextWithBackground::changeText(std::string txt) {
	message = txt;
	changeTextTextures();
}
TextWithBackground::~TextWithBackground() {
	for (auto a : text) {
		delete a;
	}
	text.clear();
}

float t = 0;
void TextWithBackground::update() {
	if (!_appearingText) return;

	t += consts::DELTA_TIME;
	if (t > .1f) {
		t = 0;
		message += finalMessage[currentIndex++];
		changeTextTextures();

		if (currentIndex >= finalMessage.size())
			_appearingText = false;
	}
}
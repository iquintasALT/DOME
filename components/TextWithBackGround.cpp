#include "TextWithBackGround.h"
#include "../sdlutils/SDLUtils.h"

TextWithBackground::TextWithBackground(std::string msg, Font & font, SDL_Color col, Texture* tex) {
	tr = nullptr;
	texture = tex;
	message = msg;
	_font = &font;
	_col = col;
}

void TextWithBackground::init() {
	tr = entity_->getComponent<Transform>();
	assert(tr != nullptr);

	Texture* t = nullptr;
	std::string str = message + " ";
	std::string second = "";
	auto renderer = sdlutils().renderer();
	return;
	do {
		second = "";
		do {
			if (t != nullptr) delete t;

			if (str.size() > 0) {
				second = str[str.size() - 1] + second;
				str.pop_back();
			}
			t = new Texture(renderer, message, *_font, _col);
			text.push_back(t);
		} while (t->width() > tr->getW() ||str.size() == 0);
		str = second;
	} while (second != "" || str.size() == 0);
}

void TextWithBackground::render() {
	SDL_Rect pos{tr->getPos().getX(), tr->getPos().getY(), tr->getW(), texture->height()};
	texture->render(pos);
	for (int i = 0; i < text.size(); i++) {
		pos.y += texture->height();
		text[i]->render(pos);
	}
}


TextWithBackground::~TextWithBackground() {
	delete texture;
	for (auto a : text) {
		delete a;
	}
	text.clear();
}
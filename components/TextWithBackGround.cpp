#include "TextWithBackGround.h"
#include "../sdlutils/SDLUtils.h"

TextWithBackground::TextWithBackground(std::string msg, Font & font, SDL_Color & col, Texture* tex) {
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
	do {
		second = "";
		do {
			if (t != nullptr) delete t;

			second = str[str.size() - 1] + second;
			str.pop_back();
			t = new Texture(renderer, message, *_font, _col);
			text.push_back(t);
		} while (t->width() > tr->getW());
		str = second;
	} while (second != "");
}

void TextWithBackground::render() {
	SDL_Rect pos{tr->getPos().getX(), tr->getPos().getY(), tr->getW(), tr->getH()};
	texture->render(pos);
	for (int i = 0; i < text.size(); i++) {
		pos.y += 10;
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
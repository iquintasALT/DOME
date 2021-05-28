#include "text_with_background.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include "../utils/checkML.h"

TextWithBackground::TextWithBackground(std::string msg, Font& font, SDL_Color col,
	Texture* tex, bool appearingText, float appearingTextSpeed, bool alignInCenter, bool txtWrap) {
	tr_ = nullptr;
	texture_ = tex;
	message_ = msg;
	font_ = &font;
	col_ = col;
	appearingText_ = appearingText;
	currentIndex = 0;
	centerAlign = alignInCenter;
	textSpeed = 1 / appearingTextSpeed;

	wrapWords = txtWrap;
	finishedWriting = false;
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
		if (centerAlign)
			pos.x -= texture_->width() / 2;
		texture_->render(pos);
	}

	SDL_Rect textPos{ tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), 10 };
	for (int i = 0; i < text_.size(); i++) {
		if (centerAlign) {
			textPos.x = tr_->getPos().getX() - text_[i]->width() / 2;
		}
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

			if (completed && str.size() > 0) { //Aqui entra si no cabe
				if (wrapWords) {
					std::string nextWord = "";
					while (str.size() > 0 && str[str.size() - 1] != ' ') { //Separa por palabras
						nextWord = str[str.size() - 1] + nextWord;
						str.pop_back();
					}

					bool removedSpace = false;
					if (str.size() > 0 && str[str.size() - 1] == ' ') {
						str.pop_back();
						removedSpace = true;
					}

					if (str.size() == 0) { //La linea de arriba se quedó vacia
						str = (removedSpace ? " " : "") + nextWord;
						second = str[str.size() - 1] + second;
						str.pop_back();
						//completed = false;
					}
					else { //
						//Añade la palabra
						second = nextWord + (removedSpace ? " " : "") + second;
					}
				}
				else {
					second = str[str.size() - 1] + second;
					str.pop_back();
				}
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

	float y = 0;
	for (int i = 0; i < text_.size(); i++)
		y += text_[i]->height();
	tr_->setH(y);
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
	if (t > textSpeed) {
		t = 0;
		message_ += finalMessage_[currentIndex++];
		changeTextTextures();

		if (currentIndex >= finalMessage_.size()) {
			appearingText_ = false;
			finishedWriting = true;
		}
	}
}

void TextWithBackground::setAlpha(int value) {
	if (texture_ != nullptr)
		texture_->setAlpha(value);
	for (auto t : text_) {
		t->setAlpha(value);
	}
}

void TextWithBackground::reset() {
	appearingText_ = true;
	finishedWriting = false;
	message_ = "";
	currentIndex = 0;

	for (int i = 0; i < text_.size(); i++)
		delete text_[i];
	text_.clear();
}

void TextWithBackground::finishWriting()
{
	appearingText_ = false;
	finishedWriting = true;
	message_ = finalMessage_;
	changeTextTextures();
}

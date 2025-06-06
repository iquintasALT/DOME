#include "pause_button.h"
#include "../sdlutils/InputHandler.h"
#include "../components/image.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundManager.h"
#include "../game/Game.h"
#include "../classes/settings_scene.h"
#include "../game/constant_variables.h"

PauseButton::PauseButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_, int type, std::string buttonName, Uint8 alpha)
	: MenuButton(pos, size, t, function, g, mngr_) {
	img = getComponent<Image>();
	over = false;
	SDL_Rect rect = { 0, 0, t->width() / 3, t->height() };
	img->setSrc(rect);
	type_ = type;
	clicked = false;
	img->enabled = false;
	img->setAlpha(alpha);
	//t = new Texture(renderer, str, *font_, col_);

	name = new Texture(sdlutils().renderer(), buttonName,
		sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0));
}

void PauseButton::update() {
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);

	if (mousePos.getX() >= position.getX() && mousePos.getY() >= position.getY() &&
		mousePos.getX() <= position.getX() + size.getX() && mousePos.getY() <= position.getY() + size.getY()) {
		if (!over) {
			soundManager().playSFX("over_button");
			over = true;
			img->changeFrame(1, 0);
		}
	}
	else {
		if (over) {
			over = false;
			img->changeFrame(0, 0);
		}
	}

	if (ih().getMouseButtonState(InputHandler::LEFT)) {
		if (over) {
			img->changeFrame(2, 0);
		}
		clicked = true;
	}
	else {
		if (clicked) {
			if (over) {
				soundManager().playSFX("push_button");
				cbOnClick(getMngr());
				if (type_ == VOLUME) {
					static_cast<SettingsScene*>(getMngr()->getGame()->getStateMachine()->currentState())->setAdjusterPosition();
				}
			}
			clicked = false;
		}
	}
}


void PauseButton::render() {
	if (over)
		img->setAlpha(200);

	img->render();
	int xPos = (int)position.getX() + 40;
	int height = (int)size.getY();
	name->render({ xPos, (int)position.getY(), name->width() * height / 50 , height });
	if (!over)
		img->setAlpha(255);
}

PauseButton::~PauseButton() {
	delete name;
}


MainMenuButton::MainMenuButton(Vector2D pos, Vector2D size, Texture* t, CallBackOnClick* function, Game* g, Manager* mngr_, int type, 
																	std::string buttonName, int alpha, float time, float displace) :
	PauseButton(pos, size, t, function, g, mngr_, type, buttonName, alpha), alpha(alpha)
{
	speed = (200 - 50) / time;

	displacementSpeed = 20 / time;
	displacement = displace;
}

MainMenuButton::~MainMenuButton() {
	//PauseButton::~PauseButton();
}

void MainMenuButton::update()
{
	PauseButton::update();

	if (over) {
		alpha += consts::DELTA_TIME * speed;
		displacement += consts::DELTA_TIME * displacementSpeed;
		if (alpha > 200)
			alpha = 200;

		if (displacement > 20)
			displacement = 20;
	}
	else
	{
		alpha -= consts::DELTA_TIME * speed;
		displacement -= consts::DELTA_TIME * displacementSpeed;
		if (alpha < 50)
			alpha = 50;

		if (displacement < 0)
			displacement = 0;
	}
}

void MainMenuButton::render() {
	img->setAlpha(int(alpha));

	img->render();
	int xPos = (int)position.getX() + 40 + displacement;
	int height = (int)size.getY();
	name->render({ xPos, (int)position.getY(), name->width() * height / 50 , height });

}

#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "controls_scene.h"
#include "../ecs/Manager.h"
#include "../classes/settings_scene.h"
#include "../classes/camera.h"
#include "../game/constant_variables.h"
#include "../components/TransitionComponent.h"
#include <string>
#include <iostream>

void MenuScene::init() {
	mngr_->getGame()->currentScene = SCENES::MAINMENU;

	float size = 1.2f;
	auto a = mngr_->addEntity();
	std::vector<Texture*> textures(5);
	for (int i = 0; i < 5; i++) {
		std::string str = "bgImage" + std::to_string(i);
		textures[i] = &sdlutils().images().at(str);
	}
	a->addComponent<ScrollingBackGround>(consts::WINDOW_WIDTH * size, consts::WINDOW_HEIGHT * size, textures, .3, true);
	mngr_->addRenderLayer<Interface>(a);
	int buttonHeight = 50;
	int ypos = consts::WINDOW_HEIGHT - 7 * buttonHeight;

	auto title = mngr_->addEntity();
	title->addComponent<Transform>(Vector2D(10, ypos - 200), 500, 250);
	title->addComponent<Image>(&sdlutils().images().at("logo"), true);
	mngr_->addRenderLayer<Interface>(title);

	auto yojhanButton = &sdlutils().images().at("yojhanButton");
	yojhanButton->setAlpha(50);
	Uint8 alpha = 50;

	int width = consts::WINDOW_WIDTH;
	auto playButton = new PauseButton(Vector2D(0, (ypos += buttonHeight)), Vector2D(width, buttonHeight * 2), yojhanButton, playGame, g_, mngr_, 0, "Play", alpha);
	mngr_->addEntity(playButton);

	ypos += buttonHeight;

	auto settingsButton = new PauseButton(Vector2D(0, (ypos += buttonHeight)), Vector2D(width, buttonHeight), yojhanButton, settings, g_, mngr_, 0, "Options", alpha);
	mngr_->addEntity(settingsButton);

	auto creditsButton = new PauseButton(Vector2D(0, (ypos += buttonHeight)), Vector2D(width, buttonHeight), yojhanButton, credits, g_, mngr_, 0, "Credits", alpha);
	mngr_->addEntity(creditsButton);

	auto exitButton = new PauseButton(Vector2D(0, (ypos += buttonHeight)), Vector2D(width, buttonHeight), yojhanButton, exit, g_, mngr_, 0, "Exit", alpha);
	mngr_->addEntity(exitButton);

	if (firstTime) {
		for (auto a : mngr_->getEntities())
			a->setActive(false);

		auto logo = mngr_->addEntity();
		logo->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
		logo->addComponent<Image>(&sdlutils().images().at("sureffect"), true);
		logo->addComponent<TransitionComponent>(3, true, [&]() {
			for (auto a : mngr_->getEntities())
				a->setActive(true);
			});
		mngr_->addRenderLayer<Interface>(logo);
	}
	// hacemos que comienze en 1 (ciclo --> numDays <= MAX_DAYS)
	getGame()->numDays++;

	soundManager().playMusic("menu_theme");
}

void MenuScene::playGame(Manager* mngr) {
	ih().clearState();
	soundManager().playMusic("game_theme");
	mngr->ChangeScene(new ControlsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void MenuScene::settings(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new SettingsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
	mngr->getGame()->currentScene = SCENES::SETTINGS;
}

void MenuScene::credits(Manager* mngr)
{
	ih().clearState();
	mngr->ChangeScene(new CreditsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
	mngr->getGame()->currentScene = SCENES::CREDITS;
}

void MenuScene::exit(Manager* mngr) {
	mngr->getGame()->quitGame();
}


ScrollingBackGround::ScrollingBackGround(int w, int h, std::vector<Texture*> textures, float sp, bool rnd) {
	index = 0;
	t = 0;
	f = 255;
	speed = sp;
	width = w;
	height = h;
	random = rnd;
	backgrounds = textures;
	black = &sdlutils().images().at("black");
	//black = backgrounds[0];
	changeOrder();
	randomPositions();
}

void ScrollingBackGround::update() {
	t += consts::DELTA_TIME * speed;

	const float fade = 0.2f;

	if (t >= 1) {
		if (++index >= backgrounds.size()) {
			index = 0;
			changeOrder();
		}
		randomPositions();
		t = 0;
		f = 255;
	}
	else if (t > 1 - fade) {
		f = (fade - 1 + t) / fade * 255;
	}
	else if (t < fade)
		f = (fade - t) / fade * 255;

	currentPos = Vector2D::Lerp(initialPos, finalPos, t);
}

void ScrollingBackGround::render() {

	bool shouldRender = true;
	Vector2D pos = Camera::mainCamera->renderRect(currentPos, width, height, shouldRender);

	if (!shouldRender) return;

	SDL_Rect dest = build_sdlrect(pos, width, height);
	backgrounds[index]->render(dest);

	black->setAlpha(f);
	black->render({ 0,0, consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT });
}

void ScrollingBackGround::changeOrder() {
	if (random) {
		int n = backgrounds.size();
		for (int i = 0; i < n; i++) {
			int random = sdlutils().rand().nextInt(0, n);
			auto aux = backgrounds[random];
			backgrounds[random] = backgrounds[i];
			backgrounds[i] = aux;
		}
	}
}

void ScrollingBackGround::randomPositions() {
	float distance_x = width - consts::WINDOW_WIDTH;
	float distance_y = height - consts::WINDOW_HEIGHT;

	float size = 2.5;

	float x = sdlutils().rand().nextInt(distance_x / size, distance_x);
	float y = sdlutils().rand().nextInt(distance_y / size, distance_y);
	initialPos = Vector2D(-x, -y);
	x = sdlutils().rand().nextInt(distance_x / size, distance_x);
	y = sdlutils().rand().nextInt(distance_y / size, distance_y);
	finalPos = Vector2D(-x, -y);
}
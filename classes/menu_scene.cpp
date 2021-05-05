#include "menu_scene.h"
#include "shelter_scene.h"
#include "raid_scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"
#include "locations_scene.h"
#include "../ecs/Manager.h"
#include "../classes/settings_scene.h"
#include "../classes/camera.h"
#include "../game/constant_variables.h"
#include <string>

void MenuScene::init() {
	/*auto pixel = mngr_->addEntity();
	pixel->addComponent<Transform>(Vector2D(0, 0), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	pixel->addComponent<Image>(&sdlutils().images().at("bgImage"), false);
	mngr_->addRenderLayer<Interface>(pixel);*/

	float size = 1.2f;
	auto a = mngr_->addEntity();
	std::vector<Texture*> textures(3);
	for (int i = 0; i < 3; i++) {
		std::string str = "bgImage" + std::to_string(i);
		textures[i] = &sdlutils().images().at(str);
	}
	a->addComponent<ScrollingBackGround>(consts::WINDOW_WIDTH * size, consts::WINDOW_HEIGHT * size, textures, .5);
	mngr_->addRenderLayer<Interface>(a);

	auto title = mngr_->addEntity();
	title->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH / 2 - 256, 150), 512, 128);
	title->addComponent<Image>(&sdlutils().images().at("titleText"), true);
	mngr_->addRenderLayer<Interface>(title);

	auto playButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 420), Vector2D(256, 64), &sdlutils().images().at("playButton"), playGame, g_, mngr_);
	mngr_->addEntity(playButton);

	auto settingsButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 500), Vector2D(256, 64), &sdlutils().images().at("settingsButton"), settings, g_, mngr_);
	mngr_->addEntity(settingsButton);

	auto exitButton = new PauseButton(Vector2D(consts::WINDOW_WIDTH / 2 - 128, 580), Vector2D(256, 64), &sdlutils().images().at("exitButton"), exit, g_, mngr_);
	mngr_->addEntity(exitButton);
}

void MenuScene::playGame(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}

void MenuScene::settings(Manager* mngr) {
	ih().clearState();
	mngr->ChangeScene(new SettingsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
	mngr->getGame()->currentScene = SCENES::SETTINGS;
}

void MenuScene::exit(Manager* mngr) {
	mngr->getGame()->quitGame();
}


ScrollingBackGround::ScrollingBackGround(int w, int h, std::vector<Texture*> textures, float sp) {
	index = 0;
	t = 0;
	speed = sp;
	width = w;
	height = h;
	backgrounds = textures;
	randomPositions();
}

void ScrollingBackGround::update() {
	t += consts::DELTA_TIME * speed;

	if (t > 1) {
		if (++index >= backgrounds.size()) index = 0;
		randomPositions();
		t = 0;
	}
	currentPos = Vector2D::Lerp(initialPos, finalPos, t);

}

void ScrollingBackGround::render() {
	bool shouldRender = true;
	Vector2D pos = Camera::mainCamera->renderRect(currentPos, width, height, shouldRender);

	if (!shouldRender) return;

	SDL_Rect dest = build_sdlrect(pos, width, height);
	backgrounds[index]->render(dest);
}

void ScrollingBackGround::randomPositions() {
	float distance_x = width - consts::WINDOW_WIDTH;
	float distance_y = height - consts::WINDOW_HEIGHT;

	float size = 2;

	float x = sdlutils().rand().nextInt(distance_x / size, distance_x);
	float y = sdlutils().rand().nextInt(distance_y / size, distance_y);
	initialPos = Vector2D(-x, -y);
	x = sdlutils().rand().nextInt(distance_x / size, distance_x);
	y = sdlutils().rand().nextInt(distance_y / size, distance_y);
	finalPos = Vector2D(-x, -y);
}
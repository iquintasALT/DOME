#include "InitialScene.h"
#include "../components/CameraMovement.h"
#include "../components/CameraShake.h"
#include "../components/Dialogue.h"
#include "../components/TransitionComponent.h"
#include "../components/InitialCameraZoom.h"
#include "../components/Timer.h"
#include "../sdlutils/SoundManager.h"
#include <iostream>


void InitialScene::init()
{
	std::string path = std::string("./resources/tilemap/initialScene.tmx");
	loadMap(path);

	auto playerTr = mngr_->getHandler<Player_hdlr>()->getComponent<Transform>();
	Vector2D pos = playerTr->getPos() + Vector2D(playerTr->getW(), playerTr->getH()) / 2;
	Camera::mainCamera->MoveToPoint(pos);
	mngr_->getHandler<Player_hdlr>()->getComponent<CameraMovement>()->enabled = false;
	mngr_->getHandler<Player_hdlr>()->getComponent<KeyboardPlayerCtrl>()->enabled = false;

	auto playExplosion = [this]() {soundManager().playSFX("initialExplosion"); };

	//playExplosion();

	auto sfx = mngr_->addEntity();
	sfx->addComponent<Timer>(2, playExplosion);

	sfx = mngr_->addEntity();
	sfx->addComponent<Timer>(3.3, playExplosion);

	sfx = mngr_->addEntity();
	sfx->addComponent<Timer>(4, playExplosion);

	auto startScene = [this]() {
		auto a = mngr_->addEntity();
		auto t = mngr_->addEntity();
		t->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
		t->addComponent<Image>(&sdlutils().images().at("black"), true);
		t->addComponent<TransitionComponent>(2);
		mngr_->addRenderLayer<ULTIMATE>(t);

		a->addComponent<CameraShake>(10, 15, 5, [this]() {
			auto cameraZoom = mngr_->addEntity();
			cameraZoom->addComponent<InitialCameraZoom>(3, 2);

			auto a = mngr_->addEntity();
			a->addComponent<Transform>(Vector2D(0, 200), 300, 400);
			auto d = a->addComponent<Dialogue>();
			std::vector<std::string> texts = {
				"It's getting pretty close", 
				"I need to hurry and pick all the things I need",
				"FAST"
			};
			d->createText(texts, 20);
			d->function = [this]() {
				auto cameraZoom = mngr_->addEntity();
				cameraZoom->addComponent<InitialCameraZoom>(1.0 / 2.7, 2);
			};
			});
	};

	auto black = mngr_->addEntity();
	black->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	auto texture = &sdlutils().images().at("black");
	texture->setAlpha(255);
	auto img = black->addComponent<Image>(texture, true);
	black->addComponent<Timer>(5, startScene);
	mngr_->addRenderLayer<ULTIMATE>(black);
}

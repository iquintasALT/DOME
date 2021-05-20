#include "InitialScene.h"
#include "../components/CameraMovement.h"
#include "../components/CameraShake.h"
#include "../components/Dialogue.h"
#include "../components/TransitionComponent.h"
#include "../components/Timer.h"
#include <iostream>
void InitialScene::init()
{
	std::string path = std::string("./resources/tilemap/initialScene.tmx");
	loadMap(path);

	Camera::mainCamera->MoveToPoint(mngr_->getHandler<Player_hdlr>()->getComponent<Transform>()->getPos());
	mngr_->getHandler<Player_hdlr>()->getComponent<CameraMovement>()->enabled = false;
	mngr_->getHandler<Player_hdlr>()->getComponent<KeyboardPlayerCtrl>()->enabled = false;


	auto startScene = [this]() {
		auto a = mngr_->addEntity();
		auto t = mngr_->addEntity();
		t->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
		t->addComponent<Image>(&sdlutils().images().at("black"), true);
		t->addComponent<TransitionComponent>(2);
		mngr_->addRenderLayer<ULTIMATE>(t);

		a->addComponent<CameraShake>(10, 15, 3, [this]() {
	
			auto a = mngr_->addEntity();
			a->addComponent<Transform>(Vector2D(0, 200), 300, 400);
			auto d = a->addComponent<Dialogue>();
			std::vector<std::string> texts = { "QUE HA SIDO ESO???", "Hmmm tendre que darme prisa" };
			d->createText(texts, 20);
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

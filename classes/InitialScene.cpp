#include "InitialScene.h"
#include "../components/CameraMovement.h"
#include "../components/CameraShake.h"
#include "../components/Dialogue.h"

#include <iostream>
void InitialScene::init()
{
	std::string path = std::string("./resources/tilemap/initialScene.tmx");
	loadMap(path);

	Camera::mainCamera->MoveToPoint(mngr_->getHandler<Player_hdlr>()->getComponent<Transform>()->getPos());
	mngr_->getHandler<Player_hdlr>()->getComponent<CameraMovement>()->enabled = false;
	auto a = mngr_->addEntity();
	a->addComponent<CameraShake>(10, 15, 3, [this]() {
		auto a = mngr_->addEntity();
		a->addComponent<Transform>(Vector2D(0,200), 300, 400);
		auto d = a->addComponent<Dialogue>();
		d->createText("QUE HA SIDO ESO???", 20);
		});
}

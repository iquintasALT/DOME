#include "InitialScene.h"
#include "../components/CameraMovement.h"
#include "../components/CameraShake.h"
#include "../components/Dialogue.h"
#include "../components/TransitionComponent.h"
#include "../components/InitialCameraZoom.h"
#include "../components/Timer.h"
#include "../sdlutils/SoundManager.h"
#include <iostream>
#include "../game/Game.h"
#include "../classes/pause_scene.h"
#include "../components/loot.h"
#include "../game/constant_variables.h"
#include "../components/TransitionComponent.h"
void InitialScene::init()
{
	auto tutorialManager = mngr_->addEntity();
	tutorialManager->addComponent<TutorialManager>();

	if (mngr_->getGame()->playerCreated)
	{
		mngr_->getGame()->playerCreated = false;
		delete mngr_->getGame()->playerSaved;
		mngr_->getGame()->playerSaved = nullptr;
	}
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

				TutorialManager::instance->changeCase(0);
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


	auto loot = mngr_->addEntity();
	mngr_->addRenderLayer<Loot>(loot);
	loot->addComponent<Transform>(playerTr->getPos() + Vector2D(300, 40), 40, 60);
	loot->addComponent<Image>(&sdlutils().images().at("panel"));
	loot->addComponent<TutorialLoot>();
}

void InitialScene::update()
{
	GameScene::update();

	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->getGame()->setShouldRenderFPS(false);
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}
TutorialManager* TutorialManager::instance = nullptr;

void TutorialManager::init()
{
	instance = this;
	currentCase = -1;
	currentMessage = nullptr;
}

void TutorialManager::update()
{
	if (currentCase == -1) return;

	switch (currentCase)
	{
	case 0:
		checkMovement();
		break;
	case 1:
		checkInventory();
		break;
	case 2:
		checkJump();
		break;
	case 3:
		checkCrouch();
		break;
	}
}

void TutorialManager::changeCase(int newcase)
{
	if (currentMessage != nullptr && !currentMessage->hasComponent<TransitionComponent>())
	{
		currentMessage->addComponent<TransitionComponent>(2);
		currentMessage = nullptr;
	}

	currentCase = newcase;
	if (newcase == -1)
		return;

	currentMessage = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<ULTIMATE>(currentMessage);
	auto tr = currentMessage->addComponent<Transform>(Vector2D(consts::WINDOW_WIDTH, consts::WINDOW_WIDTH - 100 - 20) / 2
		- Vector2D(400, 0) / 2,
		400, 100);

	switch (currentCase)
	{
	case 0:
		currentMessage->addComponent<Image>(&sdlutils().images().at("horizontal"), true);
		break;
	}
}

void TutorialManager::checkMovement()
{
	if (ih().isKeyDown(SDLK_a) ||
		ih().isKeyDown(SDLK_d)) {
		std::cout << "Te has movido bro" << std::endl;
		changeCase(-1);
	}
}

void TutorialManager::checkJump()
{
}

void TutorialManager::checkInventory()
{
}

void TutorialManager::checkCrouch()
{
}

void TutorialManager::checkShoot()
{
}

TutorialLoot::TutorialLoot()
	: Loot("Press E to open loot", 5, 5)
{
	isTutorial = true;
}


void TutorialLoot::init()
{
	Loot::init();
	inventory->storeItem(new Item(ItemInfo::mecanicalComponents(), entity_->getMngr(), inventory, 0, 0));
	inventory->storeItem(new Item(ItemInfo::food(), entity_->getMngr(), inventory, 2, 3));
}

void TutorialLoot::Interact()
{
	Loot::Interact();
	if (!isOpen) {
		if (inventory->getItems().size() == 0) {
			std::cout << "Hola";
		}
	}
}

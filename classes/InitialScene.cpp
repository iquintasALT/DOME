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
#include "../components/TextWithBackGround.h"
#include "../game/Game.h"
#include "../classes/physiognomy.h"
#include "../components/enemy_detection_component.h"
#include "../components/enemy_animation.h"
#include "../components/enemy_contact_damege.h"
#include "../components/enemy_attack_component.h"
#include "../components/enemy_behaviour_component.h"
#include "../classes/locations_scene.h"

void InitialScene::init()
{
	Camera::mainCamera->restoreScale();

	if (mngr_->getGame()->playerCreated)
	{
		mngr_->getGame()->playerCreated = false;
		delete mngr_->getGame()->playerSaved;
		mngr_->getGame()->playerSaved = nullptr;
	}

	std::string path = std::string("./resources/tilemap/initialScene.tmx");
	loadMap(path);

	auto tutorialentity = mngr_->addEntity();
	auto tutorialManager = tutorialentity->addComponent<TutorialManager>();

	auto playerTr = mngr_->getHandler<Player_hdlr>()->getComponent<Transform>();
	Vector2D pos = playerTr->getPos() + Vector2D(playerTr->getW(), playerTr->getH()) / 2;
	Camera::mainCamera->MoveToPoint(pos);
	mngr_->getHandler<Player_hdlr>()->getComponent<CameraMovement>()->enabled = false;
	mngr_->getHandler<Player_hdlr>()->getComponent<KeyboardPlayerCtrl>()->enabled = false;


	auto playExplosion = [this]() {soundManager().playSFX("initialExplosion"); };

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
				"It is getting pretty close",
				"I need to hurry and pick all the things I need and go back home",
				"FAST"
			};
			d->createText(texts, 20);
			d->function = [this]() {
				auto cameraZoom = mngr_->addEntity();
				cameraZoom->addComponent<InitialCameraZoom>(1.2 / 3, 2);

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


	initialCollider = entity_->getMngr()->addEntity();
	Vector2D initialColliderPos = Vector2D(Camera::mainCamera->getCameraPosition().getX() + 100,
		entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>()->getPos().getY());
	initialCollider->addComponent<Transform>(initialColliderPos, 30, 100);
	initialCollider->addComponent<BoxCollider>();

	trigger = nullptr;
	triggerPos = Vector2D(-50, 0) + entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<Transform>()->getPos();


	for (auto a : entity_->getMngr()->getEntities()) {
		if (a->hasComponent<TutorialBackToShelter>()) {
			backToShelter = a;
			break;
		}
	}
}

void TutorialManager::update()
{
	if (currentCase == -1) return;

	switch (currentCase)
	{
	case 0:
		checkMovement();
		break;
	case 6:
		checkShoot();
		break;
	}
}

void TutorialManager::changeCase(int newcase)
{
	if (newcase == currentCase) return;
	if (currentMessage != nullptr && !currentMessage->hasComponent<TransitionComponent>())
	{
		currentMessage->addComponent<TransitionComponent>(2);
		currentMessage = nullptr;
	}

	currentCase = newcase;
	if (newcase == -1)
		return;

	switch (currentCase)
	{
	case 0: {
		currentMessage = entity_->getMngr()->addEntity();
		entity_->getMngr()->addRenderLayer<ULTIMATE>(currentMessage);

		auto tr = currentMessage->addComponent<Transform>(
			Vector2D(consts::WINDOW_WIDTH / 2, consts::WINDOW_HEIGHT - 100 - 20)
			- Vector2D(400, 0) / 2,
			400, 100);
		currentMessage->addComponent<Image>(&sdlutils().images().at("horizontal"), true);
		break;
	}
	case 1: {
		currentMessage = entity_->getMngr()->addEntity();
		entity_->getMngr()->addRenderLayer<ULTIMATE>(currentMessage);

		currentMessage->addComponent<Transform>(Vector2D(
			consts::WINDOW_WIDTH / 2, consts::WINDOW_HEIGHT * 0.8 + 32), consts::WINDOW_WIDTH, 100);
		currentMessage->addComponent<TextWithBackground>("I need to take all the loot I can",
			sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xfffffffff), nullptr, false, 1, true);
		break;
	}
	case 2: { // create trigger

		initialCollider->setDead(true);
		initialCollider = nullptr;


		auto player = entity_->getMngr()->getHandler<Player_hdlr>();
		player->getComponent<KeyboardPlayerCtrl>()->resetSpeed();
		player->getComponent<KeyboardPlayerCtrl>()->enabled = false;

		auto a = entity_->getMngr()->addEntity();
		a->addComponent<Transform>(Vector2D(0, 200), 300, 400);
		auto d = a->addComponent<Dialogue>();
		std::vector<std::string> texts = {
			"This should be enought for today",
			"I need to head to the exit before it's too late"
		};
		d->createText(texts, 20);

		trigger = entity_->getMngr()->addEntity();
		trigger->addComponent<Transform>(triggerPos + Vector2D(0, 20), 30, 50);
		trigger->addComponent<BoxCollider>(true);
		trigger->addComponent<TutorialTrigger>();
		break;
	}
	case 3: { //Move to focus point
		trigger->setDead(true);
		trigger = nullptr;

		auto player = entity_->getMngr()->getHandler<Player_hdlr>();
		player->getComponent<KeyboardPlayerCtrl>()->resetSpeed();
		player->getComponent<KeyboardPlayerCtrl>()->enabled = false;

		auto cameraZoom = entity_->getMngr()->addEntity();
		cameraZoom->addComponent<InitialCameraZoom>(3 / 1.2, 2);

		auto a = entity_->getMngr()->addEntity();
		a->addComponent<Transform>(Vector2D(0, 200), 300, 400);
		auto d = a->addComponent<Dialogue>();

		//TODO: play sound
		d->movePlayerAtTheEnd = false;
		std::vector<std::string> texts = {
			". . .",
			"I hear something at the end of the corridor"
		};
		d->createText(texts, 20);
		d->function = [this]() {
			auto cameraZoom = entity_->getMngr()->addEntity();
			cameraZoom->addComponent<InitialCameraZoom>(1.2 / 3, 2);

			auto player = entity_->getMngr()->getHandler<Player_hdlr>();

			auto cameraMovement = entity_->getMngr()->addEntity();
			auto f = [this]() {
				auto miniTimer = entity_->getMngr()->addEntity();
				miniTimer->addComponent<Timer>(1, [this]() {changeCase(4); });
			};

			cameraMovement->addComponent<TutorialCameraMovement>(
				Vector2D(backToShelter->getComponent<Transform>()->getPos()), f, 0.7f);
		};
		break;
	}
	case 4: { //Move back to player
		auto cameraMovement = entity_->getMngr()->addEntity();
		auto f = [this]() {
			auto miniTimer = entity_->getMngr()->addEntity();
			miniTimer->addComponent<Timer>(1, [this]() {changeCase(5); });
		};
		auto player = entity_->getMngr()->getHandler<Player_hdlr>();
		auto playerTr = player->getComponent<Transform>();
		cameraMovement->addComponent<TutorialCameraMovement>(
			playerTr->getPos() + Vector2D(playerTr->getW(), playerTr->getH()) / 2.0, f, 0.9f);
		break;
	}
	case 5: //Wait 1 second and let the player move freely now
	{
		auto player = entity_->getMngr()->getHandler<Player_hdlr>();
		player->getComponent<KeyboardPlayerCtrl>()->enabled = true;
		player->getComponent<KeyboardPlayerCtrl>()->resetSpeed();

		player->getComponent<CameraMovement>()->enabled = true;

		trigger = entity_->getMngr()->addEntity();
		trigger->addComponent<Transform>(
			player->getComponent<Transform>()->getPos()
			- Vector2D(300, 0)
			+ Vector2D(-50, 20), 30, 50);
		trigger->addComponent<BoxCollider>(true);
		trigger->addComponent<TutorialTrigger>(6);

		enemy = new DefaultEnemy(entity_->getMngr(),
			trigger->getComponent<Transform>()->getPos() +
			Vector2D(-consts::WINDOW_WIDTH / 3 + 100, -20));
		enemy->getComponent<DistanceDetection>()->enabled = false;
		enemy->getComponent<Image>()->setFlip(SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		enemy->getComponent<ChasePlayer>()->enabled = false;
		enemy->getComponent<EnemyAnimation>()->enabled = false;
		enemy->getComponent<EnemyAttackComponent>()->enabled = false;
		break;
	}
	case 6: {
		trigger->setDead(true);
		trigger = nullptr;

		auto player = entity_->getMngr()->getHandler<Player_hdlr>();
	
		auto a = entity_->getMngr()->addEntity();
		a->addComponent<Transform>(Vector2D(0, 200), 300, 400);
		auto d = a->addComponent<Dialogue>();

		player->getComponent<KeyboardPlayerCtrl>()->enabled = false;
		player->getComponent<KeyboardPlayerCtrl>()->resetSpeed();
		d->movePlayerAtTheEnd = true;
		std::vector<std::string> texts = {
			"Oh caspitas!",
			"I think I can take one down..."
		};
		d->createText(texts, 20);
		d->function = [this]() {
			changeCase(7);
		};

		break;
	}
	case 7:
	{
		currentMessage = entity_->getMngr()->addEntity();
		entity_->getMngr()->addRenderLayer<ULTIMATE>(currentMessage);
		currentMessage->addComponent<Transform>(Vector2D(
			consts::WINDOW_WIDTH / 2, consts::WINDOW_HEIGHT * 0.8 + 32), consts::WINDOW_WIDTH, 100);
		currentMessage->addComponent<TextWithBackground>("Press MBL to shoot and X to change Weapon",
			sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xfffffffff), nullptr, false, 1, true);


		enemy->getComponent<DistanceDetection>()->enabled = true;
		enemy->getComponent<ChasePlayer>()->enabled = true;
		enemy->getComponent<EnemyAnimation>()->enabled = true;
		enemy->getComponent<EnemyAttackComponent>()->enabled = true;

		break;
	}
	}
}

void TutorialManager::checkMovement()
{
	if (ih().isKeyDown(SDLK_a) ||
		ih().isKeyDown(SDLK_d)) {
		changeCase(-1);
	}
}

void TutorialManager::checkShoot()
{
	if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
		changeCase(-1);
	}
}


TutorialLoot::TutorialLoot()
	: Loot("Press E to open loot", 5, 5)
{
	isTutorial = true;
	firstTime = true;
	firstTimeClosing = true;
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
			if (firstTimeClosing) {
				TutorialManager::instance->changeCase(2);
				firstTimeClosing = false;
			}
		}
	}
}

void TutorialLoot::CollisionEnter()
{
	InteractableElement::CollisionEnter();
	if (firstTime) {
		TutorialManager::instance->changeCase(1);
		firstTime = false;
	}
}

void TutorialTrigger::OnTrigger(Entity* e)
{
	if (e == entity_->getMngr()->getHandler<Player_hdlr>()) {
		TutorialManager::instance->changeCase(i);
	}
}

void TutorialCameraMovement::update()
{
	Camera::mainCamera->Lerp(destination, speed);

	float magnitude = (Camera::mainCamera->getCameraCenterPoisition() - destination).magnitude();
	std::cout << magnitude << std::endl;
	if (magnitude <= 15.0) {
		function();
		entity_->setDead(true);
	}
}

void TutorialBackToShelter::Interact()
{
	if (alreadyPressed) return;

	/*Vector2D pos;
	for (auto ent : entity_->getMngr()->getEntities()) {
		if (ent->hasGroup<INITIALGRP>()) {
			pos = ent->getComponent<Transform>()->getPos();
		}
	}*/

	auto start = [this]() {
		float time = .4;
		int n = 6;
		for (int i = 0; i <= n; i++) {
			auto timer = entity_->getMngr()->addEntity();
			auto function = [this, i, n]() {
				changeImage(n, i);
				soundManager().playSFX("boom");
			};

			float t = i * time;
			if (i == n)
				t = (i + 1) * time;
			timer->addComponent<Timer>(t, function);
		}
	};

	auto timer = entity_->getMngr()->addEntity();
	timer->addComponent<Timer>(.5, start);

	auto player_ = entity_->getMngr()->getHandler<Player_hdlr>();
	player_->getComponent<CameraMovement>()->enabled = false;
}

void TutorialBackToShelter::changeScene() {
	auto player_ = entity_->getMngr()->getHandler<Player_hdlr>();
	entity_->getMngr()->getGame()->setShouldRenderFPS(true);
	static_cast<Player*>(player_)->getPhysiognomy()->removeAllStates();

	entity_->getMngr()->ChangeScene(new LocationsScene(entity_->getMngr()->getGame()), SceneManager::SceneMode::OVERRIDE);
}

void TutorialBackToShelter::changeImage(int n, int i)
{
	if (i == n) {
		auto timer = entity_->getMngr()->addEntity();
		timer->addComponent<Timer>(3, [this]() {changeScene(); });

		auto b = entity_->getMngr()->addEntity();
		entity_->getMngr()->addRenderLayer<ULTIMATE>(b);
		b->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
		b->addComponent<Image>(&sdlutils().images().at("logo"), true);
		return;
	}
	int width = ceil(consts::WINDOW_WIDTH / float(n));
	Vector2D pos = Vector2D(floor(consts::WINDOW_WIDTH - width * (i + 1)), 0);

	auto b = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<ULTIMATE>(b);
	b->addComponent<Transform>(pos, width, consts::WINDOW_HEIGHT);
	b->addComponent<Image>(&sdlutils().images().at("black"), true);
}

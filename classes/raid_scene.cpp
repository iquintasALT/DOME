#include "raid_scene.h"
#include "../game/Game.h"
#include "hud.h"
#include "../classes/pause_scene.h"
#include "../classes/camera.h"
#include "../sdlutils/InputHandler.h"
#include "../components/transitionComponent.h";
#include "../components/TextWithBackGround.h"
#include "../components/loot.h"
#include "../classes/physiognomy.h"
#include "../classes/countdown.h"

void RaidScene::init() {
	loadMap(path_);

	timer = new Countdown(consts::RAID_TIME);

	player = static_cast<Player*>(mngr_->getHandler<Player_hdlr>());
	raidTimeEnded = false;

	auto weapon = player->getCurrentWeapon();

	if (!weapon->isActive())
		weapon->setActive(true);

	hud* h = new hud(mngr_, new Transform(Vector2D(100, 100), 64, 64, 0), player, timer);

	auto a = mngr_->addEntity();
	a->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	a->addComponent<Image>(&sdlutils().images().at("sky"))->setScrollFactor(0);
	mngr_->addRenderLayer<Parallax>(a);

	auto b = mngr_->addEntity();
	b->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	b->addComponent<Image>(&sdlutils().images().at("houses4"))->setScrollFactor(0.1);
	mngr_->addRenderLayer<Parallax>(b);

	auto c = mngr_->addEntity();
	c->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	c->addComponent<Image>(&sdlutils().images().at("houses3"))->setScrollFactor(0.2);
	mngr_->addRenderLayer<Parallax>(c);

	auto d = mngr_->addEntity();
	d->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	d->addComponent<Image>(&sdlutils().images().at("houses2"))->setScrollFactor(0.3);
	mngr_->addRenderLayer<Parallax>(d);

	auto e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	e->addComponent<Image>(&sdlutils().images().at("houses1"))->setScrollFactor(0.4);
	mngr_->addRenderLayer<Parallax>(e);

	auto f = mngr_->addEntity();
	f->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	f->addComponent<Image>(&sdlutils().images().at("wall"))->setScrollFactor(0.5);
	mngr_->addRenderLayer<Parallax>(f);

	auto g = mngr_->addEntity();
	g->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	g->addComponent<Image>(&sdlutils().images().at("road"))->setScrollFactor(0.6);
	mngr_->addRenderLayer<Parallax>(g);

	//Entity* l = mngr_->addEntity();
	//l->addComponent<Transform>(Vector2D(150, 556), 100, 100);
	//l->addComponent<Image>(&sdlutils().images().at("dust"));
	//l->addComponent<Loot>("Press E to open the loot", 5, 5);
	//mngr_->addRenderLayer<Player>(l);

	createTransition();
}

void RaidScene::update() {
	GameScene::update();

	if (!raidTimeEnded) {
		if (!timer->keepPlaying()) {
			player->getPhysiognomy()->addHypothermiaState();
			raidTimeEnded = true;
		}
	}
	
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		mngr_->ChangeScene(new PauseScene(mngr_->getGame()), SceneManager::SceneMode::ADDITIVE);
	}
}
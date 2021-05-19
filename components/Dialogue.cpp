#include "Dialogue.h"
#include "TextWithBackGround.h"
#include "Image.h"

#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/constant_variables.h"
#include "../sdlutils/SDLUtils.h"

#include "KeyboardPlayerCtrl.h"
#include "Timer.h"

void Dialogue::init()
{
	text = nullptr;
}

void Dialogue::update()
{
	if (text != nullptr && text->finishedWriting) {
		if (ih().isKeyDown(SDLK_SPACE)) {
			text->getEntity()->setDead(true);
			background->setDead(true);

			text = nullptr;
			background = nullptr;
			auto timer = entity_->getMngr()->addEntity();
			timer->addComponent<Timer>(0.5f, [this]() {
				Entity* ent = entity_->getMngr()->getHandler<Player_hdlr>();
				ent->getComponent<KeyboardPlayerCtrl>()->enabled = true;
				entity_->setDead(true);
				});
		}
	}
}

void Dialogue::createText(std::string txt, float speed)
{
	background = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<Interface>(background);
	background->addComponent<Transform>(
		Vector2D(0, consts::WINDOW_HEIGHT - 200), consts::WINDOW_WIDTH, 200);
	auto a = background->addComponent<Image>(&sdlutils().images().at("panel"), true);

	Entity* ent = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<Interface>(ent);
	ent->addComponent<Transform>(
		Vector2D(50, consts::WINDOW_HEIGHT - 150), consts::WINDOW_WIDTH - 50, 200);
	text = ent->addComponent<TextWithBackground>(txt, sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xfffffffff), nullptr, true, speed, false);

	Entity* player = entity_->getMngr()->getHandler<Player_hdlr>();
	player->getComponent<KeyboardPlayerCtrl>()->enabled = false;

}

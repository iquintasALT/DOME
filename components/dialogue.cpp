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

Dialogue::Dialogue(int height) :
	height(height)
{
	text = nullptr;
	index = -1;

	textSpeed = 1;

	function = []() {};

	justPressed = false;

	movePlayerAtTheEnd = true;
}



void Dialogue::update()
{
	if (text != nullptr) {
		if (ih().isKeyDown(SDLK_SPACE)) {
			if (justPressed) return;
			justPressed = true;
			if (text->finishedWriting) {
				text->getEntity()->setDead(true);
				text = nullptr;

				if (++index > 0 && index < texts.size()) { //Continue
					showText(texts[index]);
				}
				else { //It is finished
					background->setDead(true);

					text = nullptr;
					background = nullptr;
					auto timer = entity_->getMngr()->addEntity();

					function();

					if (movePlayerAtTheEnd)
						timer->addComponent<Timer>(0.5f, [this]() {
						Entity* ent = entity_->getMngr()->getHandler<Player_hdlr>();
						ent->getComponent<KeyboardPlayerCtrl>()->enabled = true;
						entity_->setDead(true);
							});
				}
			}
			else {
				text->finishWriting();
			}
		}
		else {
			justPressed = false;
		}
	}
}

void Dialogue::createText(std::string txt, float speed)
{
	textSpeed = speed;

	index = -1;

	showBackground();
	showText(txt);

	Entity* player = entity_->getMngr()->getHandler<Player_hdlr>();
	player->getComponent<KeyboardPlayerCtrl>()->enabled = false;
}

void Dialogue::createText(std::vector<std::string> texts, float speed)
{
	this->texts = texts;
	createText(texts[0], speed);
	index = 0;
}

void Dialogue::showBackground() {
	background = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<Interface>(background);
	background->addComponent<Transform>(
		Vector2D(0, consts::WINDOW_HEIGHT - height), consts::WINDOW_WIDTH, height);
	background->addComponent<Image>(&sdlutils().images().at("dialogbg"), true);
}

void Dialogue::showText(std::string txt)
{
	Entity* ent = entity_->getMngr()->addEntity();
	entity_->getMngr()->addRenderLayer<Interface>(ent);
	ent->addComponent<Transform>(
		Vector2D(50, consts::WINDOW_HEIGHT - height + 50), consts::WINDOW_WIDTH - 50, height);
	text = ent->addComponent<TextWithBackground>(txt, sdlutils().fonts().at("OrbitronRegular"), build_sdlcolor(0xFFFFFFFF), nullptr, true, textSpeed, false);
}

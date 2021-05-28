#include "hold_to_skip.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/constant_variables.h"
#include <iostream>

HoldToSkip::HoldToSkip(float maxTime, std::function<void()> f, bool isTutorial):
	isTutorial(isTutorial)
{
	t = 0;
	maxT = maxTime;
	function = f;
	skipButton = isTutorial ? SDL_KeyCode::SDLK_p : SDL_KeyCode::SDLK_SPACE;
}

void HoldToSkip::init()
{
	image = entity_->getComponent<Image>();
	transform = entity_->getComponent<Transform>();
	image->enabled = false;
}

void HoldToSkip::update()
{
	if (ih().isKeyDown(skipButton) ||  (!isTutorial && ih().getMouseButtonState(InputHandler::LEFT))) {
		t += consts::DELTA_TIME;

		if (t > maxT) {
			function();
			t = 0;
		}
	}
	else {
		t = 0;
	}
}

void HoldToSkip::render() {
	for (float i = 0; i < t / maxT * 360; i += 9) {
		transform->setRot(i);
		image->render();
	}
}

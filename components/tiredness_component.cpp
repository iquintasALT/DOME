#include "tiredness_component.h"
#include "../sdlutils/InputHandler.h"

void TirednessComponent::init() {
	t = new Texture(sdlutils().renderer(), "TIREDNESS: " + std::to_string((int)tiredness), sdlutils().fonts().at("ARIAL24"),
		build_sdlcolor(0xffffffff));
}
void TirednessComponent::update() {
	if (ih().isKeyDown(SDLK_2)) {
		sleep(20);
	}

	if (sdlutils().currRealTime() > tirednessTime + 5000) {
		tirednessTime = sdlutils().currRealTime();
		tiredness--;
	}
}
void TirednessComponent::render() {
	delete t;
	t = new Texture(sdlutils().renderer(), "TIREDNESS: " + std::to_string((int)tiredness), sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	t->render(position.getX(), position.getY());
}
void TirednessComponent::sleep(float tiredness_) {
	tiredness += tiredness_;
	if (tiredness > MAX_TIREDNESS) tiredness = MAX_TIREDNESS;
}

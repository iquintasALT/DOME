#include "hunger_component.h"
#include "../sdlutils/InputHandler.h"

void HungerComponent::init() {
	t = new Texture(sdlutils().renderer(), "HUNGER: " + std::to_string((int)hunger), sdlutils().fonts().at("ARIAL24"),
		build_sdlcolor(0xffffffff));
}
void HungerComponent::update() {
	if (ih().isKeyDown(SDLK_1)) {
		eat(20);
	}

	if (sdlutils().currRealTime() > hungerTime + 5000) {
		hungerTime = sdlutils().currRealTime();
		hunger--;
	}
}
void HungerComponent::render() {
	delete t;
	t = new Texture(sdlutils().renderer(), "HUNGER: " + std::to_string((int)hunger), sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	t->render(position.getX(), position.getY());
}
void HungerComponent::eat(float hunger_) {
	hunger += hunger;
	if (hunger > MAX_HUNGER) hunger = MAX_HUNGER;
}

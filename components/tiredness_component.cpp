#include "tiredness_component.h"

#include "../game/constant_variables.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"

#include "../utils/checkML.h"
#include "../utils/Vector2D.h"

#include "../components/Transform.h"
#include "../components/KeyboardPlayerCtrl.h"

TirednessComponent::TirednessComponent() : tiredness(1.0f), tirednessLev(TirednessLevel::NONE), kb(nullptr) {};

void TirednessComponent::init() {
	kb = entity_->getComponent<KeyboardPlayerCtrl>();
	assert(kb != nullptr);
}

void TirednessComponent::sleep(int hours) {
	float tirednessRestored = ((hours * 100) / consts::MAX_SLEEP_HOURS) / 100;
	tiredness += tirednessRestored;
	if (tiredness > 1.0f) tiredness = 1.0f;
	updateLevel();
}

void TirednessComponent::decreaseTiredness(float tiredness_) {
	tiredness - tiredness_ < 0.0f ? tiredness = 0.0f : tiredness -= tiredness_;
	updateLevel();
}

void TirednessComponent::setTirednessFloat(float tiredness_)
{
	tiredness < 0.0f ? tiredness = 0.0f : tiredness == tiredness_;
	updateLevel();
}

void TirednessComponent::calculatePlayerSpeed() const {
	float vel = consts::PLAYER_SPEED;

	if (tiredness >= consts::NONETIRED_LEVEL) vel *= 1.0f;
	else if (tiredness >= consts::TIRED_LEVEL) vel *= 0.8f;
	else vel = vel *= 0.66f;

	kb->setMaxSpeed(vel);
}

void TirednessComponent::updateLevel() {
	if (tiredness >= consts::NONETIRED_LEVEL) tirednessLev = TirednessLevel::NONE;
	else if (tiredness >= consts::TIRED_LEVEL) tirednessLev = TirednessLevel::TIRED;
	else tirednessLev = TirednessLevel::EXHAUSTED;

	calculatePlayerSpeed();
}
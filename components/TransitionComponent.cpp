#include "../components/TransitionComponent.h"
#include "../components/TextWithBackGround.h"
#include "../components/Image.h"
#include "../game/constant_variables.h"

TransitionComponent::TransitionComponent(float t, bool fadeOut,  std::function<void()> f) {
	fadeIn = !fadeOut;
	currentTime = 0;
	maxTime = t;

	function = f;
	image = nullptr;
	text = nullptr;
}

void TransitionComponent::init() {
	image = entity_->getComponent<Image>();
	text = entity_->getComponent<TextWithBackground>();
}

void TransitionComponent::update() {
	currentTime += consts::DELTA_TIME;
	int value = (int)(((maxTime - currentTime) / maxTime) * 255);
	if (fadeIn) value = 255 - value;

	if (text != nullptr)
		text->setAlpha(value);
	if (image != nullptr)
		image->setAlpha(value);

	if (currentTime > maxTime) {
		function();
		entity_->setDead(true);
	}
}
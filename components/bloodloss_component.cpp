#include "bloodloss_component.h"
#include "../classes/player.h"
#include "../classes/physiognomy.h"

void BloodlossComponent::init() {
	frameIndex = 13;
	count = 1;
	renderPriority = -1;
}

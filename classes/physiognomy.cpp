#include "physiognomy.h"

void Physiognomy::harm(float damage) {
	health -= damage;
	if (health < 0) health = 0;
}
void Physiognomy::heal(float life) {
	health += life;
	if (health > MAX_HEALTH) health = MAX_HEALTH;
}
bool Physiognomy::alive() {
	return health > 0;
}

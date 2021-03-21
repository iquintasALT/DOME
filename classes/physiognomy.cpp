#include "physiognomy.h"

bool Physiognomy::alive() {
	return healthComponents.size() < MAX_MULTIPLE_STATES;
}
#include "Timer.h"
#include "../ecs/Entity.h"
#include "../game/constant_variables.h"
Timer::Timer(float duration, std::function<void()> f):
	duration(duration), function(f)
{
	t = 0;
}

void Timer::update()
{
	t += consts::DELTA_TIME;

	if (t > duration) {
		function();
		entity_->setDead(true);
	}
}

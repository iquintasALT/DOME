#include "camera_shake.h"

#include "../sdlutils/SDLUtils.h"

#include "../classes/camera.h"
#include "../game/constant_variables.h"
#include "../ecs/Entity.h"
CameraShake::CameraShake(float strength, float speed,  float duration, std::function<void()> f):
	strength(strength), duration(duration), speed(speed), function(f)
{
	t = 0;

	//float x = sdlutils().rand().nextInt(-10, 10) / 10.0f;
	//float y = sdlutils().rand().nextInt(-10, 10) / 10.0f;

	float x = 10;
	float y = -10;

	dir = Vector2D(x, y).normalize();
}

void CameraShake::update()
{
	t += consts::DELTA_TIME;

	float s = speed;
	int r = 
		(t * speed);

	if (r % 2 != 0) s *= -1;

	s *= duration - t;

	Camera::mainCamera->MoveDir(dir * consts::DELTA_TIME * s * strength);

	if (t > duration)
	{
		function();
		entity_->setDead(true);
	}
}



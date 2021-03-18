#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../game/constant_variables.h"
#include "../classes/camera.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include <vector>

class ParticleSystem: public Component
{
public:
	ParticleSystem(Texture* tex, int rows, int cols, int r, int c);
	~ParticleSystem();
	void update() override;
	void init() override;
	void render() override;

	int width;
	int height;
	float distanceToOrigin;
	Vector2D dir;
	float angleDispersion;
	float lifeTime;
	float initialRotation;
	float speed;
	int count;
	bool burst;

private:
	Texture* texture;
	SDL_Rect source;
	std::vector<Transform*> particles;
	std::vector<float> particleLife;
	
	Transform* transform;

	inline int randomInt(int min, int max);
	void spawnParticle();
};


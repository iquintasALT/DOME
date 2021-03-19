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
	ParticleSystem(Transform* parent, Texture* tex, int rows, int cols, int r, int c);
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
	int rateOverTime;

	bool worldPosition;
	bool gravity;
	float gravityValue = 9.8;
	bool inheritVelocity;
private:
	Texture* texture;
	SDL_Rect source;
	std::vector<Transform*> particles;
	std::vector<float> particleLife;
	
	Transform* parentTransform;

	Transform* transform;

	float rateTimer = 0;

	inline int randomInt(int min, int max);
	void spawnParticle();
};


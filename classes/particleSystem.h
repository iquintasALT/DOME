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
#include "../game/checkML.h"

class ParticleSystem : public Component
{
private:
	Texture* texture;
	SDL_Rect source;
	vector<Transform*> particles;
	vector<float> particleLife;

	int actualBurstCount = 0;

	bool destroyParticles = false;

	Transform* transform;

	float rateTimer = 0;
	float burstTimer = 0;
	float time = 0;

	inline int randomInt(int min, int max);
	void spawnParticle();

public:
	struct Function {
	private:
		float m3, m2, m;
		float n;
	public:
		Function() {
			m3 = m2 = m = n = 0;
		}
		Function(float x) {
			m = x;
			n = m3 = m2 = 0;
		};
		Function(float _m, float _n) {
			m = _m;
			n = _n;
			m3 = m2 = 0;
		};
		Function(float _m2, float _m, float _n) {
			m = _m;
			n = _n;
			m2 = _m2;
			m3 = 0;
		};
		Function(float _m3, float _m2, float _m, float _n) {
			m = _m;
			n = _n;
			m2 = _m2;
			m3 = _m3;
		};
		float Evaluate(float x) {
			float p3 = m3 * x * x * x;
			float p2 = m2 * x * x;
			float p1 = m * x;
			return p3 + p2 + p1 + n;
		};
	};

	ParticleSystem(Texture* tex, int rows, int cols, int r, int c);
	~ParticleSystem();
	void update() override;
	void init() override;
	void render() override;

	int width;
	int height;
	float distanceToOrigin;

	Vector2D dir;
	Vector2D offset;

	float angleDispersion;
	float lifeTime;
	float initialRotation;
	float speed;
	int count;
	bool burst;
	float rateOverTime;

	float particleScale = 1;

	bool worldPosition;
	bool gravity;
	float gravityValue = 9.8;
	bool inheritVelocity;
	float inheritVelocityMultiplier = 1;
	bool playOnAwake = true;
	int burstCount;
	float burstDuration;
	bool sizeOverTime;

	bool destroyAfterBurst;
	int burstRepeat = 1;

	bool destroyAfterTime = false;
	float timeToDestroy;

	bool emitting;

	Function sizeCurve;

	void Play();
	void Stop();
	void Burst();
};


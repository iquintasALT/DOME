#include "particleSystem.h"
#include <iostream>
#include <math.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

struct ParticleSystem::DynamicBody {
public:
	RigidBody* rb;
	Transform* tr;

	DynamicBody(Transform* _tr, Vector2D vel) {
		tr = _tr;
		rb = new RigidBody(vel, tr);
	}
	~DynamicBody() {
		delete tr;
		delete rb;
	}
};

ParticleSystem::ParticleSystem(Texture* tex, int rows, int cols, int r, int c) :
	texture(tex) {
	int w = tex->width() / cols;
	int h = tex->height() / rows;

	width = texture->width()/ cols;
	height = texture->height()/ rows;

	source = { w * c ,h * r,w,h };

	//Particle properties
	lifeTime = .7;
	distanceToOrigin = 0;
	speed = 2;
	angleDispersion = 30;
	dir = Vector2D(0, 1).normalize();
	rateOverTime = 6;
	rateTimer = 0;
	worldPosition = true;
	gravity = true;
	gravityValue = 9.8;
	inheritVelocity = false;
	inheritVelocityMultiplier = -1;
	emitting = playOnAwake;
	offset = Vector2D(10, height / 2 + 10);
	particleScale = .8;
	sizeOverTime = true;
	sizeCurve = Function(-1, 0, 1);

	burst = false;
	burstCount = 10;
	burstTimer = 20;
	burstDuration = 2;

	timeToDestroy = 3;
}

ParticleSystem::~ParticleSystem() {
	for (auto a : particles) {
		delete a;
	}
	particles.clear();
	particleLife.clear();
}

void ParticleSystem::init() {
	transform = entity_->getComponent<Transform>();
	assert(transform != nullptr);

	rb = entity_->getComponent<RigidBody>();

	//width *= particleScale;
	//height *= particleScale;

	offset = Vector2D(0, transform->getH());
}

void ParticleSystem::update() {
	if (emitting && !destroyParticles) {
		rateTimer += consts::DELTA_TIME;

		if (rateTimer > 1.0 / rateOverTime) {
			spawnParticle();
			rateTimer = 0;
		}

		if (destroyAfterTime) {
			time += consts::DELTA_TIME;

			if (time > timeToDestroy)
				destroyParticles = true;
		}
	}

	if (burst) {
		burstTimer += consts::DELTA_TIME;

		if (burstTimer > burstDuration) {
			Burst();
			burstTimer = 0;
		}
	}


	if (particles.size() <= 0) return;

	//maybe delete particles in a separate loop
	for (int i = 0; i < particles.size(); i++) {
		auto a = particles[i];

		a->rb->update();

		float life = particleLife[i];
		a->tr->setW(particleScale * width * sizeCurve.Evaluate((lifeTime - life) / lifeTime));
		a->tr->setH(particleScale * height * sizeCurve.Evaluate((lifeTime - life) / lifeTime));

		if (gravity)
			a->rb->setVel(a->rb->getVel() + Vector2D(0, gravityValue * consts::DELTA_TIME));
		particleLife[i] -= consts::DELTA_TIME;

		if (particleLife[i] < 0) {
			particleLife.erase(particleLife.begin() + i);
			delete particles[i];
			particles.erase(particles.begin() + i);

			if (destroyParticles && particles.size() <= 0) {
				std::cout << std::endl << "Destroyed particles" << std::endl;
				entity_->setDead(true);
			}
		}
	}
}
void ParticleSystem::render() {
	for (auto a : particles) {
		auto transform_ = a->tr;
		bool shouldRender = true;
		Vector2D relPos = transform_->getPos();
		if (!worldPosition) relPos = relPos + transform->getPos();
		Vector2D pos = Camera::mainCamera->renderRect(relPos, transform_->getW(), transform_->getH(), shouldRender);


		if (shouldRender) {
			float scale = Camera::mainCamera->getScale();
			SDL_Rect dest{ pos.getX(), pos.getY(), transform_->getW(), transform_->getH() };
			dest.x = floor(dest.x * scale);
			dest.y = floor(dest.y * scale);
			dest.w = ceil(dest.w * scale);
			dest.h = ceil(dest.h * scale);
			texture->render(source, dest, transform_->getRot(), nullptr, SDL_FLIP_NONE);
		}
	}
}

void ParticleSystem::spawnParticle() {
	Vector2D particleOrigin = Vector2D(randomInt(-10, 11), randomInt(-10, 11)).normalize() * distanceToOrigin + offset;

	if (worldPosition) particleOrigin = particleOrigin + transform->getPos();

	float rot = randomInt(-100, 101) / 100.0;
	float angle = degreesToRadians(angleDispersion * rot / 2);
	Vector2D particleSpeed = Vector2D(
		cos(angle) * dir.getX() - sin(angle) * dir.getY(),
		sin(angle) * dir.getX() - cos(angle) * dir.getY()) * speed;

	if (inheritVelocity && rb != nullptr)
		particleSpeed = particleSpeed + rb->getVel() * inheritVelocityMultiplier;

	particles.push_back(new DynamicBody(new Transform(particleOrigin, width, height, 0), particleSpeed));
	particleLife.push_back(lifeTime);
}

int ParticleSystem::randomInt(int min, int max) {
	return min + rand() % (max - min);
}

void ParticleSystem::Play() {
	emitting = true;
	rateTimer = 0;
}
void ParticleSystem::Stop() {
	emitting = false;
}

void ParticleSystem::Burst() {
	if (destroyAfterBurst && actualBurstCount++ >= burstRepeat)
	{
		destroyParticles = true;
		return;
	}

	for (int i = 0; i < burstCount; i++) {
		spawnParticle();
	}

}


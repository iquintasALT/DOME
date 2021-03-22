#include "particleSystem.h"
#include <iostream>
#include <math.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

ParticleSystem::ParticleSystem(Texture* tex, int rows, int cols, int r, int c) :
	texture(tex) {
	int w = tex->width() / cols;
	int h = tex->height() / rows;

	width = texture->width() * particleScale / cols;
	height = texture->height() * particleScale / rows;

	source = { w * c ,h * r,w,h };

	//Particle properties
	lifeTime = 1;
	distanceToOrigin = 0;
	speed = 4;
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
	particleScale = 1;
	sizeOverTime = true;
	sizeCurve = Function(-1, 0, 1);

	burst = false;
	burstCount = 10;
	burstTimer = 20;
	burstDuration = 2;
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

	width *= particleScale;
	height *= particleScale;

	offset = Vector2D(0, transform->getH());
}

void ParticleSystem::update() {
	if (emitting) {
		rateTimer += consts::DELTA_TIME;

		if (rateTimer > 1.0 / rateOverTime) {
			spawnParticle();
			rateTimer = 0;
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

		a->update();

		float life = particleLife[i];
		a->setW(width * sizeCurve.Evaluate((lifeTime - life) / lifeTime));
		a->setH(height * sizeCurve.Evaluate((lifeTime - life) / lifeTime));

		if (gravity)
			a->setVel(a->getVel() + Vector2D(0, gravityValue * consts::DELTA_TIME));
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
	for (auto transform_ : particles) {
		bool shouldRender = true;
		Vector2D relPos = transform_->getPos();
		if (!worldPosition) relPos = relPos + transform->getPos();
		Vector2D pos = Camera::mainCamera->renderRect(relPos, transform_->getW(), transform_->getH(), shouldRender);

		if (shouldRender)
			texture->render(source, build_sdlrect(pos, transform_->getW(), transform_->getH()), transform_->getRot(), nullptr, SDL_FLIP_NONE);
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

	if (inheritVelocity)
		particleSpeed = particleSpeed + transform->getVel() * inheritVelocityMultiplier;

	particles.push_back(new Transform(particleOrigin, particleSpeed, width, height, 0));
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
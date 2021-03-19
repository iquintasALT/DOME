#include "particleSystem.h"
#include <iostream>
#include <math.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

ParticleSystem::ParticleSystem(Transform* parent, Texture* tex, int rows, int cols, int r, int c) :
	texture(tex), parentTransform(parent) {
	int w = tex->width() / cols;
	int h = tex->height() / rows;

	width = texture->width() * particleScale / cols;
	height = texture->height() * particleScale / rows;

	source = { w * c ,h * r,w,h };

	//Particle properties
	lifeTime = 10;
	distanceToOrigin = 0;
	speed = 2;
	angleDispersion = 30;
	dir = Vector2D(0, 1).normalize();
	rateOverTime = 3;
	rateTimer = 0;
	worldPosition = true;
	gravity = true;
	inheritVelocity = true;
	inheritVelocityMultiplier = -1;
	emitting = playOnAwake;
	offset = Vector2D(0, 10);
	particleScale = .5;
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
}

void ParticleSystem::update() {
	if (emitting) {
		rateTimer += consts::DELTA_TIME;

		if (rateTimer > 1.0 / rateOverTime) {
			spawnParticle();
			rateTimer = 0;
		}
	}

	if (particles.size() <= 0) return;

	for (auto a : particles) {
		a->update();

		if (gravity)
			a->setVel(a->getVel() + Vector2D(0, gravityValue * consts::DELTA_TIME));
	}

	for (int i = 0; i < particles.size(); i++) {
		particleLife[i] -= consts::DELTA_TIME;

		if (particleLife[i] < 0) {
			particleLife.erase(particleLife.begin() + i);
			delete particles[i];
			particles.erase(particles.begin() + i);
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
		particleSpeed = particleSpeed + parentTransform->getVel() * inheritVelocityMultiplier;

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
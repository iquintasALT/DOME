#include "particleSystem.h"
#include <iostream>
#include <math.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

ParticleSystem::ParticleSystem(Texture* tex, int rows, int cols, int r, int c) :
	texture(tex) {
	int w = tex->width() / cols;
	int h = tex->height() / rows;
	source = { w * c ,h * r,w,h };
	lifeTime = 1;
	distanceToOrigin = 0;
	speed = 1;
	initialRotation = 50;
	dir = Vector2D(1, 0);
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

	width = transform->getW();
	height = transform->getH();

	assert(transform != nullptr);

	for (int i = 0; i < 10; i++)
		spawnParticle();
}

void ParticleSystem::update() {
	if (particles.size() <= 0) return;

	for (auto a : particles) {
		a->update();
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
		Vector2D relPos = transform->getPos() + transform_->getPos();
		Vector2D pos = Camera::mainCamera->renderRect(relPos, transform_->getW(), transform_->getH(), shouldRender);

		if (shouldRender)
			texture->render(source, build_sdlrect(pos, transform_->getW(), transform_->getH()), transform_->getRot(), nullptr, SDL_FLIP_NONE);
	}
}

void ParticleSystem::spawnParticle() {
	//Vector2D particleSpeed = Vector2D(randomInt(-10, 11), randomInt(-10, 11)).normalize() * speed;

	Vector2D particleOrigin = transform->getPos() + Vector2D(randomInt(-10, 11), randomInt(-10, 11)).normalize() * distanceToOrigin;

	float rot = randomInt(-100, 101) / 100.0;
	float angle = degreesToRadians(rot);
	Vector2D particleSpeed = Vector2D(
		cos(angle) * dir.getX() - sin(angle) * dir.getY(),
		sin(angle) * dir.getX() - cos(angle) * dir.getY()) * speed;

	particles.push_back(new Transform(particleOrigin, particleSpeed, width, height, 0));
	particleLife.push_back(lifeTime);
}

int ParticleSystem::randomInt(int min, int max) {
	return min + rand() % max;
}
#include "animation_component.h"

void AnimationComponent::Animation::setImage(Image* img) {
	image = img;
	assert(image != nullptr);
	width = image->getSrc().w;
	height = image->getSrc().h;
}

AnimationComponent::Animation::Animation(int frame, int frameCount, bool loop, float animationSpeed) {
	this->frameCount = frameCount;
	frameRow = frame;
	currentFrame = 0;
	speed = animationSpeed * frameCount * consts::DELTA_TIME;
	this->loop = loop;
	image = nullptr; width = height = 0;
}

void AnimationComponent::Animation::advanceFrame() {
	if (++currentFrame >= frameCount) {
		if (loop)
			currentFrame = 0;
		else currentFrame = frameCount - 1;
	}

	render();
}

void AnimationComponent::Animation::render() {
	SDL_Rect source{ currentFrame * width, frameRow * height, width, height };
	image->setSrc(source);
}
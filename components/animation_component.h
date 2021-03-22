#pragma once

#include "../ecs/Component.h"
#include "../components/Image.h"
#include "../game/checkML.h"
#include "../game/constant_variables.h"

class animation_component : public Component {
protected:
	struct Animation {
	protected:
		static Image* image;
		static int width, height;

		int frameRow;
		int frameCount;
		int currentFrame;
		float speed;
		bool loop;
	public:
		static void setImage(Image* img) {
			image = img;
			assert(image != nullptr);
			width = image->getSrc().w;
			height = image->getSrc().h;
		}

		Animation(int frame, int frameCount, bool loop = true, float animationSpeed = 1) {
			this->frameCount = frameCount;
			frameRow = frame;
			currentFrame = 0;
			speed = animationSpeed * frameCount * consts::DELTA_TIME;
			this->loop = loop;
		}

		void advanceFrame() {
			if (++currentFrame >= frameCount) {
				if (loop)
					currentFrame = 0;
				else currentFrame = frameCount - 1;
			}

			render();
		}

		void render() {
			SDL_Rect source{ currentFrame * width, frameRow * height, width, height };
			image->setSrc(source);
		}

		bool operator == (Animation& other) {
			return frameRow == other.frameRow;
		}

		bool operator != (Animation& other) {
			return frameRow != other.frameRow;
		}

		float animationSpeed() { return speed; };
	};

public:
	animation_component() {};

	virtual ~animation_component() {};
};
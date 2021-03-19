#pragma once

#include "../ecs/Component.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../game/constant_variables.h"
#include "../components/KeyboardPlayerCtrl.h"

#include <iostream>

class player_animation : public Component {
public:
	player_animation() : im_(nullptr), tr_(nullptr) {
		frameX_ = 0; frameY_ = 0; frameDivision = 3;
	};

	virtual void init();

	virtual ~player_animation() {};

	void playerWalk();

	virtual void update();

private:
	struct Animation {
	private:
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
			speed = animationSpeed  * frameCount * consts::DELTA_TIME;
			this->loop = loop;
		}

		void advanceFrame() {
			if (++currentFrame >= frameCount ) {
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

	const enum animations_name { iddle = 0, walking, crouch };
	Animation animations[3]{
	Animation(iddle, 3),
	Animation(walking, 14),
	Animation(crouch, 3) };

	Animation currentAnimation = animations[iddle];
	float timer = 0;


	bool changeAnimations();
//-----------------------------------------------------------------------------
	Image* im_;
	Transform* tr_;
	KeyboardPlayerCtrl* ctrl;

	int frameX_; int frameY_;
	float frameTime = 0;
	int frameDivision;
};
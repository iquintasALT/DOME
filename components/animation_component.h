#pragma once

#include "../ecs/Component.h"
#include "../components/Image.h"
#include "../utils/checkML.h"
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
		Animation(int frame, int frameCount, bool loop = true, float animationSpeed = 1);

		static void setImage(Image* img);

		void advanceFrame();

		void render();

		inline bool operator == (Animation& other) { return frameRow == other.frameRow; }

		inline bool operator != (Animation& other) { return frameRow != other.frameRow; }

		inline float animationSpeed() { return speed; };
	};

public:
	inline animation_component() {};

	inline virtual ~animation_component() {};
};
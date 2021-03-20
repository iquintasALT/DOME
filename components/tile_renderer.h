#pragma once

#include <vector>
#include <map>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/checkML.h"

#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"

using namespace std;

class TileRenderer : public Component {
public:
	TileRenderer(Texture* tset, int x = 0, int y = 0, 
		int tx = 0, int ty = 0, int w = 0, int h = 0);

	virtual ~TileRenderer() {};

	void render() override;

private:
	Texture* sheet;
	// x, y en el mundo
	int x, y;
	// x, y en el spritesheet
	int tx, ty;
	// ancho y alto del tile
	int width, height;
};

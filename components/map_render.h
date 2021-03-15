#pragma once

#include <vector>
#include <map>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"

#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"

using namespace std;

using gid = int;

struct Tile {
	Texture* sheet;
	// x, y coordinate in the world
	int x, y;
	// the x, y coordinate on the sprite sheet
	int tx, ty;
	int width;
	int height;

	Tile(Texture* tset, int x = 0, int y = 0,
		int tx = 0, int ty = 0, int w = 0, int h = 0);
	void draw();
};

class MapRender : public Component {
public:
	MapRender(string& const path) : path_(path) { }

	virtual ~MapRender() { }

	void render() override {
		
	}

private:
	tmx::Map tile_map;

	string path_;
	int rows, cols;
	int tile_width, tile_height;
	vector<Tile> tiles;
	map<gid, Texture*> tilesets;

	void load();
};

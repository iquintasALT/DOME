#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>

#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"

#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

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

class Map {
public:
	static void addMap(Manager* mngr, string& const path) {

	}

private:
	tmx::Map tile_map;

    int rows, cols;
    int tile_width, tile_height;
	vector<Tile> tiles;
	map<gid, Texture*> tilesets;

    void load(string& const path);
};

#endif
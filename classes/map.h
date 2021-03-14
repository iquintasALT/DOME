#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>

#include "tmxlite/Map.hpp"
#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"

using namespace std;

using name = string;

struct Tile {
    Texture* sheet;
    // x coordinate in the world
    int x;
    // y coordinate in the world
    int y;
    // the x coordinate on the sprite sheet
    int tx;
    // the y coordinate on the sprite sheet
    int ty;
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

	vector<int> tiles;
	map<name, Texture*> tilesets;
};

#endif
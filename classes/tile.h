#ifndef MAP_H
#define MAP_H

#include "../ecs/Manager.h"
#include "../components/tile_renderer.h"
#include "../utils/checkML.h"

using namespace std;

class Tile {
public:
	Tile(Manager* mngr, Texture* tset, string layer, int x = 0, int y = 0,
		int tx = 0, int ty = 0, int w = 0, int h = 0, SDL_Texture* tex = nullptr);
};

#endif
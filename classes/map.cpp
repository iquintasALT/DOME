#include "map.h"
#include "../ecs/Entity.h"

Tile::Tile(Manager* mngr, Texture* tset, int x, int y, int tx, int ty, int w, int h) {
	auto tile = mngr->addEntity();
	tile->addComponent<TileRenderer>(tset, x, y, tx, ty, w, h);
}
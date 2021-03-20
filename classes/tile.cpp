#include "tile.h"
#include "../ecs/Entity.h"

Tile::Tile(Manager* mngr, Texture* tset, bool wall, int x, int y, int tx, int ty, int w, int h) {
	auto tile = mngr->addEntity();
	if (wall) tile->setGroup<Wall_grp>(true);
	tile->addComponent<TileRenderer>(tset, x, y, tx, ty, w, h);
}
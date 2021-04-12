#include "tile.h"
#include "../ecs/Entity.h"

Tile::Tile(Manager* mngr, Texture* tset, string layer, int x, int y, int tx, int ty, int w, int h) {
	auto tile = mngr->addEntity();
	tile->addComponent<TileRenderer>(tset, x, y, tx, ty, w, h);

	if(layer == string("Background"))
		mngr->addRenderLayer<Background>(tile);
	else 
		mngr->addRenderLayer<Walls>(tile);
}
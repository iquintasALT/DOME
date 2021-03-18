#ifndef MAP_H
#define MAP_H

#include <string>

#include "../ecs/Manager.h"
#include "../components/map_render.h"
#include "../game/checkML.h"

using namespace std;

class Map {
public:
	static void addMap(Manager* mngr, string& const path) {
        Entity* map = mngr->addEntity();
        map->addComponent<MapRender>(path);
	}
};

#endif
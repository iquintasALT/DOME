#ifndef MAP_H
#define MAP_H

#include <string>

#include "../ecs/Manager.h"

class Map {
public:
	void addMap(Manager* mngr) {
        Entity* map = mngr->addEntity();
        //map->addComponent<MapRender>();
	}
};

#endif
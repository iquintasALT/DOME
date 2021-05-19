#include "InitialScene.h"

void InitialScene::init()
{
	std::string path = std::string("./resources/tilemap/initialScene.tmx");
	loadMap(path);
}

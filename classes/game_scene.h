#pragma once

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/tile.h"
#include "../components/box_collider.h"
#include "../components/InventoryController.h"
#include "../classes/particleSystem.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "../game/checkML.h"

#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/ObjectGroup.hpp"
#include "tmxlite/Tileset.hpp"

#include <memory>

using namespace std;

using gid = unsigned int;

struct MapInfo {
	tmx::Map tile_map;
	string path_;
	int rows, cols;
	int tile_width, tile_height;
	map<gid, Texture*> tilesets;
};

class GameScene
{
protected:
	Manager* mngr_;
	MapInfo mapInfo;

	//funcion de cargado de mapa usable por todas las escenas de juego
	void loadMap(string& const path);

public:
	//constructora que crea el manager de gObjects de la clase
	inline GameScene() { mngr_ = new Manager(); }
	inline ~GameScene() { delete mngr_; }
	//creacion de objetos, que sera diferente en cada escena
	inline virtual void init() = 0;
	//metodos para llamar al manager de la escena
	inline void update() { mngr_->update(); }
	inline void refresh() { mngr_->refresh(); }
	inline virtual void render() { mngr_->render(); }
};


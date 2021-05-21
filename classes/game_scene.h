#pragma once

#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../components/box_collider.h"
#include "../components/InventoryController.h"
#include "../components/particleSystem.h"
#include "../classes/weapon_behaviour.h"
#include "../classes/player.h"
#include "../classes/enemy.h"
#include "../components/loot.h"
#include "../classes/camera.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "../utils/checkML.h"

#include "./tmxlite/Map.hpp"
#include "./tmxlite/Layer.hpp"
#include "./tmxlite/TileLayer.hpp"
#include "./tmxlite/ObjectGroup.hpp"
#include "./tmxlite/Tileset.hpp"

#include <memory>

using namespace std;

using gid = unsigned int;

class Game;

struct MapInfo {
	tmx::Map* tile_map;
	string path_;
	int rows, cols;
	int tile_width, tile_height;
	map<gid, Texture*> tilesets;

	MapInfo() {
		tile_map = nullptr;
		path_ = "";
		rows = cols = tile_width = tile_height = 0;
	}
	~MapInfo() {
		if(tile_map != nullptr)
		delete tile_map;
	}
};

class GameScene
{
protected:
	string name;
	Manager* mngr_;
	MapInfo mapInfo;
	Game* g_;
	Texture* background;
	void createTransition(float timeToFade = 2, bool fadeIn = true, std::function<void()> f = []() {}, string transitionText = "");

	void createParallaxLayer(float scrollFactor, Texture* t, int numOfRep);
	virtual void createParallaxBackground(int numOfRep) {};

	// funcion de cargado de mapa usable por todas las escenas de juego
	void loadMap(string& const path);

public:
	//constructora que crea el manager de gObjects de la clase
	inline GameScene(Game* game, string sceneName) { background = nullptr; mngr_ = new Manager(game); g_ = game; name = sceneName; }
	inline virtual ~GameScene() { delete mngr_; if (background != nullptr) delete background; }
	//creacion de objetos, que sera diferente en cada escena
	inline virtual void init() = 0;
	inline virtual void onLoad() {};
	//metodos para llamar al manager de la escena
	inline virtual void update() { mngr_->update(); }
	inline virtual void refresh() { mngr_->refresh(); }
	inline virtual void render() { mngr_->render(); }
	inline virtual void cycle() { update(); refresh(); render(); mngr_->cycle(); }
	inline Game* getGame() { return g_; };
	void changeState(GameScene* gs);
};

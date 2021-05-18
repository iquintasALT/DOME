#include "game_scene.h"
#include "../game/Game.h"
#include "../components/back_to_shelter.h"
#include "../components/TextWithBackGround.h"
#include "../components/Transform.h"
#include "../components/Image.h"

#include "../components/TransitionComponent.h"
#include "../game/Game.h"
#include "../components/parallax_component.h"


void GameScene::loadMap(string& const path) {
	// cargamos el mapa .tmx del archivo indicado

	mapInfo.tile_map = new tmx::Map();
	mapInfo.tile_map->load(path);

	// obtenemos el tama�o del mapa (en tiles)
	auto map_dimensions = mapInfo.tile_map->getTileCount();
	mapInfo.rows = map_dimensions.y;
	mapInfo.cols = map_dimensions.x;

	// calculamos las dimensiones de los tiles
	auto tilesize = mapInfo.tile_map->getTileSize();
	mapInfo.tile_width = tilesize.x;
	mapInfo.tile_height = tilesize.y;

	// establecemos los bordes de la camara con respecto al numero de tiles en el mapa
	Camera::mainCamera->setBounds(0, 0, mapInfo.cols * mapInfo.tile_width, mapInfo.rows * mapInfo.tile_height);

	// cargamos y almacenamos los tilesets utilizados por el tilemap
	// (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
	// (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
	// el nombre del archivo sin extension en el .json) 
	auto& map_tilesets = mapInfo.tile_map->getTilesets();
	for (auto& tset : map_tilesets) {
		string name = tset.getName();
		Texture* tex = &sdlutils().tilesets().find(name)->second;
		mapInfo.tilesets.insert(std::pair<gid, Texture*>(tset.getFirstGID(), tex));
	}


	int sceneLoots = 0;
	// recorremos cada una de las capas (de momento solo las de tiles) del mapa
	auto& map_layers = mapInfo.tile_map->getLayers();
	for (auto& layer : map_layers) {
		// aqui comprobamos que sea la capa de tiles
		if (layer->getType() == tmx::Layer::Type::Tile) {
			// cargamos la capa
			tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());

			// obtenemos sus tiles
			auto& layer_tiles = tile_layer->getTiles();

			// recorremos todos los tiles para obtener su informacion
			for (auto y = 0; y < mapInfo.rows; ++y) {
				for (auto x = 0; x < mapInfo.cols; ++x) {
					// obtenemos el indice relativo del tile en el mapa de tiles
					auto tile_index = x + (y * mapInfo.cols);

					// con dicho indice obtenemos el indice del tile dentro de su tileset
					auto cur_gid = layer_tiles[tile_index].ID;

					// si es 0 esta vacio asi que continuamos a la siguiente iteracion
					if (cur_gid == 0)
						continue;

					// guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
					// el mas cercano, y a la vez menor, al gid del tile)
					auto tset_gid = -1, tsx_file = 0;;
					for (auto& ts : mapInfo.tilesets) {
						if (ts.first <= cur_gid) {
							tset_gid = ts.first;
							tsx_file++;
						}
						else
							break;
					}

					// si no hay tileset v�lido, continuamos a la siguiente iteracion
					if (tset_gid == -1)
						continue;

					// normalizamos el �ndice
					cur_gid -= tset_gid;

					// calculamos dimensiones del tileset
					auto ts_width = 0;
					auto ts_height = 0;
					SDL_QueryTexture(mapInfo.tilesets[tset_gid]->getSDLTexture(),
						NULL, NULL, &ts_width, &ts_height);

					// calculamos el area del tileset que corresponde al dibujo del tile
					auto region_x = (cur_gid % (ts_width / mapInfo.tile_width)) * mapInfo.tile_width;
					auto region_y = (cur_gid / (ts_width / mapInfo.tile_width)) * mapInfo.tile_height;

					// calculamos la posicion del tile
					auto x_pos = x * mapInfo.tile_width;
					auto y_pos = y * mapInfo.tile_height;


					//bool is_wall = false; // Booleano de control
					//// Acceso a las propiedades de una tile dentro de un tileset (.tsx)
					//vector<tmx::Property> tile_props = mapInfo.tile_map.getTilesets()[tsx_file - 1].getTiles()[cur_gid].properties;
					//if (tile_props.size() > 0) {
					//	// Lo separo aqui por si en algun futuro creamos m�s propiedades, realmente habria que hacer una busqueda
					//	// de la propiedad y si esta en el vector usarla acorde
					//	if (tile_props[0].getName() == "wall")
					//		is_wall = tile_props[0].getBoolValue();
					//}

					//propiedades de la capa de tiles
					vector<tmx::Property> tl_props = tile_layer->getProperties();

					// metemos el tile
					Tile(mngr_, mapInfo.tilesets[tset_gid], tl_props[0].getStringValue(), x_pos, y_pos,
						region_x, region_y, mapInfo.tile_width, mapInfo.tile_height);
				}
			}
		}
		if (layer->getType() == tmx::Layer::Type::Object) {
			tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());

			auto& objs = object_layer->getObjects();


			for (auto obj : objs) {
				auto aabb = obj.getAABB();

				if (obj.getName() == "collision") {
					auto collider = mngr_->addEntity();
					collider->setGroup<Wall_grp>(true);
					collider->addComponent<Transform>(Point2D(aabb.left, aabb.top), aabb.width, aabb.height);
					collider->addComponent<BoxCollider>(false, 0);
				}
				else if (obj.getName() == "ladder") {
					auto stair = mngr_->addEntity();
					stair->setGroup<Ladders_grp>(true);
					stair->addComponent<Transform>(Point2D(aabb.left, aabb.top), aabb.width, aabb.height);
					stair->addComponent<BoxCollider>(true, 0);
				}
				else if (obj.getName() == "playerSpawn") {
					if (g_->playerCreated)
						mngr_->getHandler<Player_hdlr>()->getComponent<Transform>()->setPos(Point2D(aabb.left, aabb.top));
					else {
						new Player(mngr_, Point2D(aabb.left, aabb.top));
						g_->playerCreated = true;
					}
					auto camPos = Vector2D(aabb.left, aabb.top) + Vector2D(0, consts::CAMERA_MARGIN_FROM_PLAYER / Camera::mainCamera->getScale());
					Camera::mainCamera->MoveToPoint(camPos);
				}
				else if (obj.getName() == "loot") {
					Entity* interactableElement = mngr_->addEntity();
					interactableElement->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					interactableElement->addComponent<Image>(&sdlutils().images().at("wardrobe"), 7, 2, 4, 0);
					mngr_->addRenderLayer<Loot>(interactableElement);
					interactableElement->addComponent<Loot>("Press E to open the loot", 5, 5);
					Loot* loot = interactableElement->getComponent<Loot>();

					vector<I> chestLoot = getGame()->SCENES_LOOT.find(getGame()->currentScene)->second[sceneLoots];
					for (int i = 0; i < chestLoot.size(); i++) {
						loot->getInventory()->storeItem(new Item{ new ItemInfo(chestLoot[i].name, chestLoot[i].desc, chestLoot[i].w,chestLoot[i].h,chestLoot[i].row,chestLoot[i].col),mngr_,loot->getInventory(),chestLoot[i].x,chestLoot[i].y });
					}
					sceneLoots++;
				}
				else if (obj.getName() == "enemy") {
					// int en objeto para identificar el tipo de enemigo
					int enemyType = obj.getProperties()[0].getIntValue();
					if (enemyType == 0)  // basico
						new DefaultEnemy(mngr_, Point2D(aabb.left, aabb.top));
					else if (enemyType == 1) // volador
						new FlyingEnemy(mngr_, Point2D(aabb.left, aabb.top));
					else // rango
						new RangedEnemy(mngr_, Point2D(aabb.left, aabb.top));
				}
				else if (obj.getName() == "returnShelter") {
					Entity* returnToShelter = mngr_->addEntity();
					returnToShelter->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					returnToShelter->addComponent<Image>(&sdlutils().images().at("back_to_shelter"), 1, 1, 0, 0);
					returnToShelter->addComponent<BackToShelter>(this);
					mngr_->addRenderLayer<Walls>(returnToShelter);
				}
				else if (obj.getName() == "sleepStation") {
					static_cast<ShelterScene*>(this)->initSleepStation({ aabb.left, aabb.top }, { aabb.width, aabb.height });
					auto interactable = mngr_->addEntity();
					interactable->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					interactable->addComponent<InteractableElement>("Press E to SLEEP");
				}
				else if (obj.getName() == "workStation") {
					static_cast<ShelterScene*>(this)->initMechWs({ aabb.left, aabb.top }, { aabb.width, aabb.height });
					auto interactable = mngr_->addEntity();
					interactable->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					interactable->addComponent<InteractableElement>("Press E to craft WAR ITEMS");
				}
				else if (obj.getName() == "medicalStation") {
					static_cast<ShelterScene*>(this)->initMedWs({ aabb.left, aabb.top }, { aabb.width, aabb.height });
					auto interactable = mngr_->addEntity();
					interactable->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					interactable->addComponent<InteractableElement>("Press E to craft MEDICAL ITEMS");
				}
				else if (obj.getName() == "spaceShip") {
					static_cast<ShelterScene*>(this)->initSpaceshipStation({ aabb.left, aabb.top }, { aabb.width, aabb.height });
					auto interactable = mngr_->addEntity();
					interactable->addComponent<Transform>(Vector2D(aabb.left, aabb.top), aabb.width, aabb.height, 0);
					interactable->addComponent<InteractableElement>("Press E to see the SHIP STATE");
				}
			}
		}
	}
}

void GameScene::changeState(GameScene* gs)
{
	mngr_->onNewScene();
	g_->getStateMachine()->changeState(gs);
}

void GameScene::createTransition(float timeToFade, bool fadeIn, std::function<void()> f) {

	int winWidth = consts::WINDOW_WIDTH;
	int winheight = consts::WINDOW_HEIGHT;

	Entity* e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(), winWidth, winheight);
	e->addComponent<Image>(&sdlutils().images().at("black"), true);
	e->addComponent<TransitionComponent>(timeToFade, fadeIn, f);
	mngr_->addRenderLayer<Interface>(e);

	e = mngr_->addEntity();
	e->addComponent<Transform>(Vector2D(winWidth / 2, winheight / 2), winWidth, winheight);
	e->addComponent<TextWithBackground>(name,
		sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff), nullptr, false, 0, true);
	e->addComponent<TransitionComponent>(timeToFade, fadeIn, f);
	mngr_->addRenderLayer<Interface>(e);
}

void GameScene::createParallaxLayer(float scrollFactor, Texture* t, int numOfRep) {
	auto layer = mngr_->addEntity();
	layer->addComponent<Transform>(Vector2D(), consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT);
	layer->addComponent<ParallaxComponent>(t, numOfRep)->setScrollFactor(scrollFactor);
	mngr_->addRenderLayer<Parallax>(layer);
}

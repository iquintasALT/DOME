#pragma once
#include <memory>
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/GravityComponent.h"
#include "../components/KeyboardPlayerCtrl.h"
#include "../components/player_animation.h"
#include "../components/weapon_behaviour.h"
#include "../components/InventoryController.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"

class GameScene
{
public:
	//constructora que crea el manager de gObjects de la clase
	GameScene() { mngr_ = new Manager(); }
	~GameScene() { delete mngr_; }
	//creacion de objetos, que sera diferente en cada escena
	virtual void init() = 0;
	//metodos para llamar al manager de la escena
	void update() { mngr_->update(); }
	void refresh() {mngr_->refresh(); }
	void render() {mngr_->render(); }

protected:
	Manager* mngr_;
};


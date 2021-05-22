#pragma once
#include "qa_selection_scene.h"

#include <vector>
#include "game_scene.h"
#include "../game/constant_variables.h"
#include "../ecs/Component.h"

class Game;
class Texture;



class qa_selection_scene : public GameScene
{
private:
	Entity* locationButton;
	Transform* locationButtonTr;

	Entity* shelterButton;
	Transform* shelterButtonTr;

public:
	qa_selection_scene(Game* g) : GameScene(g, "qa"){};
	~qa_selection_scene() {};
	 
	void init() override;
	void onLoad() override {};
	void update() override;
};


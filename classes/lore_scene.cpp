#include "lore_scene.h"
#include "../game/constant_variables.h"
#include "locations_scene.h"


void LoreScene::init()
{
	float size = 1.2f;
	auto a = mngr_->addEntity();
	std::vector<Texture*> textures(5);
	for (int i = 0; i < 5; i++) {
		std::string str = "lore" + std::to_string(i);
		textures[i] = &sdlutils().images().at(str);
	}
	a->addComponent<ChangeImage>(textures, .3, this);
	mngr_->addRenderLayer<Interface>(a);
}


void LoreScene::update()
{

}


void LoreScene::StartGame(Manager* mngr)
{
	ih().clearState();
	mngr->ChangeScene(new LocationsScene(mngr->getGame()), SceneManager::SceneMode::ADDITIVE);
}


ChangeImage::ChangeImage(std::vector<Texture*> textures, float sp, LoreScene* l) 
{
	index = 0;
	t = 0;
	f = 255;
	speed = sp;
	width = consts::WINDOW_WIDTH;
	height = consts::WINDOW_HEIGHT;
	backgrounds = textures;
	black = &sdlutils().images().at("black");
	position = Vector2D(0, 0);
	lore = l;
}

void ChangeImage::update() {
	t += consts::DELTA_TIME * speed;


	const float fade = 0.2f;

	if (t >= 1) {
		if (++index >= backgrounds.size()) {
			//Cambiar de escena a juego
			lore->StartGame(entity_->getMngr());
		}
		t = 0;
		f = 255;
	}
	else if (t > 1 - fade) {
		f = (fade - 1 + t) / fade * 255;
	}
	else if (t < fade)
		f = (fade - t) / fade * 255;
}

void ChangeImage::render() {

	bool shouldRender = true;
	Vector2D pos = Camera::mainCamera->renderRect(position, width, height, shouldRender);

	if (!shouldRender) return;

	SDL_Rect dest = build_sdlrect(pos, width, height);
	backgrounds[index]->render(dest);

	black->setAlpha(f);
	black->render({ 0,0, consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT });
}
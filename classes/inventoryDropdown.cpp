#include "inventoryDropdown.h"
#include "../sdlutils/SDLUtils.h"
inventoryDropdown::slot::slot(std::string text, std::function<void()> f) {
	function = f;
	texture = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff));
}
inventoryDropdown::slot::~slot() {
	if (texture != nullptr)
		delete texture;
	texture = nullptr;
}

inventoryDropdown::inventoryDropdown(Texture* texture, std::vector<inventoryDropdown::slot*> slot, float width) : slots(slot), texture(texture), width(width) {
}

inventoryDropdown::~inventoryDropdown() {
	for (auto s : slots) {
		delete s;
	}
	slots.clear();
}

void inventoryDropdown::render() {
	SDL_Rect rect{ position.getX(), position.getY(), width, 0 };
	for (auto slot : slots) {
		int h = slot->texture->height();
		rect.h = h;
		rect.w = width;
		texture->render(rect);
		rect.w = std::min(slot->texture->width(), (int)width);
		slot->texture->render(rect);
		rect.y += h;
	}
}

bool inventoryDropdown::onClick(Vector2D& const mousePos) {
	const float x = mousePos.getX();
	const float y = mousePos.getY();
	float posy = position.getY();
	if (x >= position.getX() && x < position.getX() + width) {
		float height = 0;
		for (auto slot : slots) {
			height =slot->texture->height();
			if (y >= posy && y < posy + height)
			{
				slot->function();
				return true;
			}
			
			posy += height;
		}
	}
	return false;
}

void inventoryDropdown::setPos(Vector2D& const mousePos) {
	position = mousePos;

}
#include "inventoryDropdown.h"
#include "../sdlutils/SDLUtils.h"
InventoryDropdown::slot::slot(std::string text, std::function<void()> f) {
	function = f;
	texture = new Texture(sdlutils().renderer(), text, sdlutils().fonts().at("Orbitron32"), build_sdlcolor(0xffffffff));
}
InventoryDropdown::slot::~slot() {
	delete texture;
	texture = nullptr;
}

InventoryDropdown::InventoryDropdown(Texture* texture,
	std::vector<InventoryDropdown::slot*> slot, float width)
	: slots(slot), texture(texture), width(width) {

}

InventoryDropdown::~InventoryDropdown() {
	for (auto s : slots) {
		delete s;
	}
	slots.clear();
}

void InventoryDropdown::render(bool isActive) {
	SDL_Rect rect{ position.getX(), position.getY(), width, 0 };

	bool first = !isActive;
	for (auto slot : slots) {
		if (first) {
			first = false;
			continue;
		}
		int h = slot->texture->height();
		rect.h = h;
		rect.w = width;
		texture->render(rect);
		rect.w = std::min(slot->texture->width(), (int)width);
		slot->texture->render(rect);
		rect.y += h;
	}
}

bool InventoryDropdown::onClick(Vector2D& const mousePos, bool isActive) {
	const float x = mousePos.getX();
	const float y = mousePos.getY();
	float posy = position.getY();
	if (x >= position.getX() && x < position.getX() + width) {
		float height = 0;
		bool skipFirst = !isActive;
		for (auto slot : slots) {
			if (skipFirst) {
				skipFirst = false;
				continue;
			}

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

void inventoryDropdown::setPos(Vector2D& const mousePos) 
{
	position = mousePos;
}

Vector2D inventoryDropdown::getPos()
{
	return position;
}

Vector2D inventoryDropdown::getDimensions()
{
	return Vector2D(width, slots.size() * texture->height());
}
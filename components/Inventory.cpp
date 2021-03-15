#include "Inventory.h"
#include "../sdlutils/InputHandler.h"

#include <iostream>
Inventory::Inventory(int width, int height) : width(width), height(height) {
	
	transform = nullptr;
	itemWidth = itemHeight = 1;
}

void Inventory::init() {
	transform = entity_->getComponent<Transform>();

	assert(transform != nullptr);

	itemWidth = transform->getW() / width;
	itemHeight = transform->getW() / height;


	storedItems.push_back(new Item(ItemInfo::bottleOfWater(), entity_->getMngr(), this, 0, 0));

}
void Inventory::render() {
	for (auto a : storedItems) {
		a->render();
	}
}

Inventory::~Inventory() {
	for (auto a : storedItems) {
		delete a;
	}
	storedItems.clear();
}

void Inventory::update() {
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	Vector2D pos = transform->getPos();
	int width = transform->getW();
	int height = transform->getH();
	int mouseX = mousePos.getX();
	int mouseY = mousePos.getY();

	if (mouseX > pos.getX() && mouseX < pos.getX() + width
		&& mouseY > pos.getY() && mouseY < pos.getY() + height)
	{
		std::cout << "HOla";



	}
}

Vector2D Inventory::itemPosition(int x, int y) {
	return transform->getPos() + Vector2D(x * itemWidth, y * itemHeight);
}
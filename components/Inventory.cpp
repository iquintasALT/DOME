#include "Inventory.h"
#include "../sdlutils/InputHandler.h"

#include <iostream>
Inventory::Inventory(int width, int height) : width(width), height(height) {
	storedItems.push_back(new Item(ItemInfo::bottleOfWater(), 0, 0));

}

void Inventory::init() {
	transform = entity_->getComponent<Transform>();
}

Inventory::~Inventory() {

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

		std::cout << "HOla";


}
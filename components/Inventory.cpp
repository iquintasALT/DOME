#include "Inventory.h"
#include "../sdlutils/InputHandler.h"

#include <iostream>
Inventory::Inventory(int width, int height) : width(width), height(height) {

	transform = nullptr;
	itemWidth = itemHeight = 1;
	selectedItem = nullptr;

	justPressed = false;
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
	int panel_width = transform->getW();
	int panel_height = transform->getH();
	int mouseX = mousePos.getX();
	int mouseY = mousePos.getY();

	if (mouseX > pos.getX() && mouseX < pos.getX() + panel_width
		&& mouseY > pos.getY() && mouseY < pos.getY() + panel_height)
	{
		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!justPressed) {
				justPressed = true;

				int xCell = (mouseX - pos.getX()) / panel_width * width;
				int yCell = (mouseY - pos.getY()) / panel_height * height;

				std::cout << xCell << " " << yCell << std::endl;
			}
		}
		else {
			if (justPressed) {
				selectedItem = nullptr;
			}

			justPressed = false;
		}


	}
}

Vector2D Inventory::itemPosition(int x, int y) {
	return transform->getPos() + Vector2D(x * itemWidth, y * itemHeight);
}
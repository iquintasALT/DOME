#include "Inventory.h"
#include "../sdlutils/InputHandler.h"
#include <iostream>

Inventory::Inventory(int width, int height) : width(width), height(height) {
	transform = nullptr;
	itemWidth = itemHeight = 1;
	selectedItem = nullptr;
	selectedItem_ = nullptr;
	justPressed = false;

	grid = std::vector<std::vector<Item*>>(width, std::vector<Item*>(height, nullptr));
}

void Inventory::init() {
	transform = entity_->getComponent<Transform>();

	assert(transform != nullptr);

	itemWidth = transform->getW() / width;
	itemHeight = transform->getW() / height;

	storeItem(new Item(ItemInfo::bottleOfWater(), entity_->getMngr(), this, 0, 0));
	storeItem(new Item(ItemInfo::medicine(), entity_->getMngr(), this, 2, 2));
	storeItem(new Item(ItemInfo::food(), entity_->getMngr(), this, 4, 0));
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

	int xCell = (mouseX - pos.getX()) / panel_width * width;
	int yCell = (mouseY - pos.getY()) / panel_height * height;

	if (mouseX > pos.getX() && mouseX < pos.getX() + panel_width
		&& mouseY > pos.getY() && mouseY < pos.getY() + panel_height)
	{
		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!justPressed) {
				justPressed = true;
				timer = 0;
				selectedItem_ = findItemInSlot(xCell, yCell);
			}
			else {
				if (selectedItem_ != nullptr) {
					timer += 1 / consts::DELTA_TIME;

					if (timer > timeToHold) {
						selectedItem = selectedItem_;
						selectedItem_ = findItemInSlot(xCell, yCell);

						if (selectedItem != selectedItem_)
							selectedItem = nullptr;

						selectedItem_ = nullptr;
					}
				}
			}
		}
		else {
			if (selectedItem) { 
				std::cout << xCell << " " << yCell << std::endl;
				if (avaliableSpace(xCell, yCell, selectedItem->width, selectedItem->height, selectedItem)) {
					moveItem(selectedItem, xCell, yCell);
				}

				selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y));
			}
			selectedItem = nullptr;
			justPressed = false;
		}
	}
	else {

	}

	if (selectedItem != nullptr) {
		if (!ih().getMouseButtonState(InputHandler::LEFT)) {
			selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y));
			selectedItem = nullptr;
		}
		else
			selectedItem->setPosition(Vector2D(ih().getMousePos().first - itemWidth / 2, ih().getMousePos().second - itemHeight / 2));
	}
}

Vector2D Inventory::itemPosition(int x, int y) {
	return transform->getPos() + Vector2D(x * itemWidth, y * itemHeight);
}

Item* Inventory::findItemInSlot(int x, int y) {
	return grid[x][y];
}

bool Inventory::avaliableSpace(int x, int y, int w, int h, Item* item) {
	if (x + w > width || y + h > height) return false;

	for (int i = x; i < width && i < x + w; i++) {
		for (int c = y; c < height && c < y + h; c++) {
			if (grid[i][c] != nullptr && grid[i][c] != item) 
				return false;
		}
	}
	return true;
}

void Inventory::storeItem(Item* item) {
	storedItems.push_back(item);

	for (int i = item->x; i < item->x + item->width; i++) {
		for (int c = item->y; c < item->y + item->height; c++) {
			grid[i][c] = item;
		}
	}
}

void Inventory::moveItem(Item* item, int x, int y) {
	for (int i = item->x; i < width && i < item->x + item->width; i++) {
		for (int c = item->y; c < height && c < item->y + item->height; c++) {
			grid[i][c] = nullptr; // Aquí estaba mal, ponía grid[x][y]
		}
	}

	item->x = x;
	item->y = y;

	for (int i = x; i < width && i < x + item->width; i++) {
		for (int c = y; c < height && c < y + item->height; c++) {
			grid[i][c] = item;
		}
	}
}
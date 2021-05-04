#include "Inventory.h"
#include "../sdlutils/InputHandler.h"
#include "../components/TextWithBackGround.h"
#include "../game/Game.h"
#include "../classes/crafting_system.h"
#include "../sdlutils/SDLUtils.h"

#include <iostream>

Inventory::Inventory(int width, int height) : width(width), height(height), other(nullptr) {
	transform = nullptr;
	selectedItem = nullptr;
	selectedItem_ = nullptr;
	justPressed = false;

	originalPos = Vector2D();

	grid = std::vector<std::vector<Item*>>(width, std::vector<Item*>(height, nullptr));

	toolTips = nullptr;
	toolTipsTr = nullptr;
	toolTipsText = nullptr;
	showToolTip = false;

	dropDown = nullptr;
	dropDownActive = false;
}
Inventory::Inventory(int width, int height, Inventory* player) : Inventory(width, height) {
	this->other = player;
	originalPos = Vector2D();
}
void Inventory::defaultPosition() {
	moveInventory(originalPos);
}

void Inventory::moveInventory(Point2D pos) {
	transform->setPos(pos);

	for (auto a : storedItems) {
		a->image->getComponent<Transform>()->setPos(itemPosition(a->x, a->y));
	}
}

void Inventory::init() {
	transform = entity_->getComponent<Transform>();
	assert(transform != nullptr);
	originalPos = transform->getPos();

	toolTips = entity_->getMngr()->addEntity();
	toolTipsTr = toolTips->addComponent<Transform>(Vector2D(100, 100), 500, 10, 0);
	toolTipsText = toolTips->addComponent<TextWithBackground>("Inventario",
		sdlutils().fonts().at("ARIAL32"), build_sdlcolor(0xffffffff), &sdlutils().images().at("tooltipBox"));
	entity_->getMngr()->addRenderLayer<ULTIMATE>(toolTips);
	toolTips->setActive(false);

	dropDownActive = false;
	std::vector<inventoryDropdown::slot*> slots;
	slots.push_back(new inventoryDropdown::slot("Use", []() { std::cout << std::endl << "Elemento usado"; }));
	slots.push_back(new inventoryDropdown::slot("Rotate", []() {std::cout << std::endl << "Elemento girado" << std::endl; }));
	slots.push_back(new inventoryDropdown::slot("Delete", [this]() {removeItem(itemClickedInDropdown); }));
	dropDown = new inventoryDropdown(&sdlutils().images().at("tooltipBox"), slots, 200);
}
void Inventory::render() {
	/*for (auto a : storedItems) {
		a->render();
		a->image->setActive(true);
	}*/

	if (dropDownActive) {
		dropDown->render();
	}

	//else if (showToolTip)
	toolTips->setActive(showToolTip);
}

void Inventory::onEnable() {
	for (auto a : storedItems) {
		a->image->setActive(true);
	}
}

void Inventory::onDisable() {
	for (auto a : storedItems) {
		a->image->setActive(false);
	}
}


Inventory::~Inventory() {
	for (auto a : storedItems) {
		delete a;
	}
	storedItems.clear();
	delete dropDown;
}

void Inventory::update() {
	Vector2D mousePos(ih().getMousePos().first, ih().getMousePos().second);
	Vector2D pos = transform->getPos();

	if (insideSquare(mousePos.getX(), mousePos.getY()))
	{
		int xCell = (mousePos.getX() - pos.getX()) / transform->getW() * width;
		int yCell = (mousePos.getY() - pos.getY()) / transform->getH() * height;

		auto hoverItem = findItemInSlot(xCell, yCell);
		showToolTip = hoverItem != nullptr;

		if (showToolTip) {
			toolTipsText->changeText(hoverItem->getItemInfo()->description());
			toolTipsTr->setPos(mousePos);
		}

		if (ih().getMouseButtonState(InputHandler::RIGHT) && selectedItem == nullptr && hoverItem != nullptr) {
			if (!dropDownActive) {
				dropDownActive = true;
				dropDown->setPos(mousePos);
				itemClickedInDropdown = hoverItem;
			}
		}

		if (dropDownActive && !justPressed && ih().getMouseButtonState(InputHandler::LEFT)) {
			dropDown->onClick(mousePos);
			dropDownActive = false;
			justPressed = true;
			itemClickedInDropdown = nullptr;
		}

		if (dropDownActive)
			return;

		if (ih().getMouseButtonState(InputHandler::LEFT)) {
			if (!justPressed && (other == nullptr || (other != nullptr && other->selectedItem == nullptr))) {

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
				if (avaliableSpace(xCell, yCell, selectedItem)) {
					moveItem(selectedItem, xCell, yCell);
				}

				selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y));
			}
			selectedItem = nullptr;
			justPressed = false;
		}
	}
	else {
		showToolTip = false;
	}

	if (selectedItem != nullptr) {
		if (!ih().getMouseButtonState(InputHandler::LEFT)) { //Interaction between items
			if (other != nullptr && other->insideSquare(mousePos.getX(), mousePos.getY(), other->transform)) {
				pos = other->transform->getPos();
				int xCell = (mousePos.getX() - pos.getX()) / other->transform->getW() * other->width;
				int yCell = (mousePos.getY() - pos.getY()) / other->transform->getH() * other->height;

				if (other->avaliableSpace(xCell, yCell, selectedItem)) {
					removeItem(selectedItem);

					selectedItem->x = xCell;
					selectedItem->y = yCell;

					other->storeItem(selectedItem);
					selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y, other->transform));

				}
				else {
					selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y));
				}

				selectedItem = nullptr;
			}
			else {
				selectedItem->setPosition(itemPosition(selectedItem->x, selectedItem->y));
				selectedItem = nullptr;
			}
		}
		else
			selectedItem->setPosition(Vector2D(ih().getMousePos().first - itemWidth / 2, ih().getMousePos().second - itemHeight / 2));
	}
}

Vector2D Inventory::itemPosition(int x, int y) {
	return transform->getPos() + Vector2D(x * itemWidth, y * itemHeight);
}
Vector2D Inventory::itemPosition(int x, int y, Transform* transform) {
	return transform->getPos() + Vector2D(x * itemWidth, y * itemHeight);
}

Item* Inventory::findItemInSlot(int x, int y) {
	return grid[x][y];
}

bool Inventory::avaliableSpace(int x, int y, Item* item) {
	if (x + item->width > width || y + item->height > height) return false;

	for (int i = x; i < width && i < x + item->width; i++) {
		for (int c = y; c < height && c < y + item->height; c++) {
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
void Inventory::removeItem(Item* item) {
	for (int i = item->x; i < width && i < item->x + item->width; i++) {
		for (int c = item->y; c < height && c < item->y + item->height; c++) {
			grid[i][c] = nullptr;
		}
	}

	storedItems.remove(item);
}

void Inventory::moveItem(Item* item, int x, int y) {
	for (int i = item->x; i < width && i < item->x + item->width; i++) {
		for (int c = item->y; c < height && c < item->y + item->height; c++) {
			grid[i][c] = nullptr;
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

int Inventory::itemWidth = 1;
int Inventory::itemHeight = 1;

void Inventory::setItemDimensions(Transform* transform, int width, int height) {
	itemWidth = transform->getW() / width;
	itemHeight = transform->getW() / height;

}

void Inventory::adjustPanelSize() {
	transform->setW(width * itemWidth);
	transform->setH(height * itemHeight);
}

void Inventory::storeDefaultItems() {
	storeItem(new Item(ItemInfo::bottleOfWater(), entity_->getMngr(), this, 0, 0));
	storeItem(new Item(ItemInfo::medicine(), entity_->getMngr(), this, 2, 2));
	storeItem(new Item(ItemInfo::food(), entity_->getMngr(), this, 4, 0));
}


bool Inventory::insideSquare(int mouseX, int mouseY, Transform* rect) {
	Vector2D& pos = rect->getPos();

	return mouseX > pos.getX() && mouseX < pos.getX() + rect->getW()
		&& mouseY > pos.getY() && mouseY < pos.getY() + rect->getH();
}
bool Inventory::insideSquare(int mouseX, int mouseY) {
	Vector2D& pos = transform->getPos();

	return mouseX > pos.getX() && mouseX < pos.getX() + transform->getW()
		&& mouseY > pos.getY() && mouseY < pos.getY() + transform->getH();
}

list<Item*>& Inventory::getItems() { return storedItems; };

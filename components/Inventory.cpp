#include "Inventory.h"

#include <iostream>
Inventory::Inventory(int width, int height): width(width), height(height) {
	storedItems.push_back(new Item(ItemInfo::bottleOfWater(), 0, 0));
}

Inventory::~Inventory() {

}


void Inventory::update() {
	std::cout << "HOla";

	for (auto a : storedItems) {

	}
}
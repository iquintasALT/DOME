#include "InventoryController.h"

InventoryController::InventoryController() {
	inventoryPanel = entity_->getMngr()->addEntity();



}

InventoryController::~InventoryController() {
	delete inventoryPanel;
}
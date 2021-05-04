#include "loot.h"
#include "../game/Game.h"
#include "../classes/crafting_system.h"

const float Loot::margin = 50;

Loot::Loot(std::string mssg, int inventoryWidth, int inventoryHeight) :
	InteractableElement(mssg),
	inventory(nullptr), playerInventory(nullptr),
	inventoryController(nullptr), inventoryEntity(nullptr) {
	isOpen = false;
	playerTransform = nullptr;
	inventoryTransform = nullptr;

	invenWidth = inventoryWidth;
	invenHeight = inventoryHeight;
}

Loot::~Loot() {

	Game* g = entity_->getMngr()->getGame();
	g->SCENES_LOOT.find(g->currentScene)->second.clear();


	vector<I> itemsInLoot;

	for (Item* i : inventory->getItems()) {
		ItemInfo* info = i->getItemInfo();
		I aux = I{ info->name(),0,info->width(),info->height(),i->getX(),i->getY(),info->row(),info->col(), info->description() };
		itemsInLoot.push_back(aux);
	}

	g->SCENES_LOOT.find(g->currentScene)->second.push_back(itemsInLoot);
}

void Loot::Interact() {
	isOpen = !isOpen;
	inventoryController->enabled = !isOpen;
	playerInventory->setOther((isOpen ? inventory : nullptr));

	if (isOpen) {
		float maxWidth = playerTransform->getW() + inventoryTransform->getW() + margin;
		float x = (sdlutils().width() - maxWidth) / 2;

		playerInventory->moveInventory(Vector2D(x, playerTransform->getPos().getY()));
	}
	else {
		playerInventory->defaultPosition();
	}

	inventoryController->OpenLoot(isOpen);
	inventoryEntity->setActive(isOpen);
}

void Loot::init() {
	InteractableElement::init();

	inventoryController = entity_->getMngr()->getHandler<Player_hdlr>()->getComponent<InventoryController>();
	playerInventory = inventoryController->inventory;

	playerTransform = playerInventory->getEntity()->getComponent<Transform>();

	assert(inventoryController != nullptr);
	assert(playerInventory != nullptr);
	assert(playerTransform != nullptr);

	inventoryEntity = entity_->getMngr()->addEntity();
	inventoryTransform = inventoryEntity->addComponent<Transform>(Vector2D(0, 0), 100, 100, 0);
	inventoryEntity->addComponent<Image>(&sdlutils().images().at("storage"), 2, 2, 1, 0, true);
	entity_->getMngr()->addRenderLayer<Interface>(inventoryEntity);

	inventory = inventoryEntity->addComponent<Inventory>(invenWidth, invenHeight);

	inventory->adjustPanelSize();
	//inventory->storeDefaultItems();
	inventory->setOther(playerInventory);


	float maxWidth = playerTransform->getW() + inventoryTransform->getW() + margin;
	float x = (sdlutils().width() - maxWidth) / 2 + playerTransform->getW() + margin;


	//inventoryTransform->setPos(Vector2D(x, playerTransform->getPos().getY()));
	inventory->moveInventory(Vector2D(x, playerTransform->getPos().getY()));



	inventoryEntity->setActive(false);
}
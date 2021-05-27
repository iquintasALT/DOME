#include "loot.h"
#include "../game/Game.h"
#include "../classes/crafting_system.h"
#include "../sdlutils/SoundManager.h"

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

	isTutorial = false;
}

Loot::~Loot() {
	if (isTutorial) return;

	Game* g = entity_->getMngr()->getGame();

	vector<pair<ItemInfo*, Vector2D>> itemsInLoot;

	for (Item* i : inventory->getItems()) {
		ItemInfo* info = i->getItemInfo();
		ItemInfo* aux =
			new ItemInfo(info);
		itemsInLoot.push_back(make_pair(aux, Vector2D(i->getX(), i->getY())));
	}

	auto* aux = &g->SCENES_LOOT.find(g->currentScene)->second;
	aux->push_back(itemsInLoot);

	auto variableAuxiliar = *aux->begin();
	for (auto variableParaRecorrerLaVariableAuxiliar : variableAuxiliar) {
		delete variableParaRecorrerLaVariableAuxiliar.first;
	}

	aux->erase(aux->begin());
}

void Loot::Interact() {
	isOpen = !isOpen;
	inventoryController->enabled = !isOpen;
	playerInventory->setOther((isOpen ? inventory : nullptr));

	if (isOpen) {
		soundManager().playSFX("open");
		float maxWidth = playerTransform->getW() + inventoryTransform->getW() + margin;
		float x = (sdlutils().width() - maxWidth) / 2;
		playerInventory->moveInventory(Vector2D(x, playerTransform->getPos().getY()));
	}
	else {
		soundManager().playSFX("close");
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
#include "SceneManager.h"
#include "../game/Game.h"

void SceneManager::ChangeScene(GameScene* scene, SceneMode mode) {
	shouldSwap = true;

	sceneToSwap = scene;
	sceneChangeMode = mode;
}

SceneManager::operator bool() const {
	return shouldSwap;
}

void SceneManager::LoadScene() {
	auto states = game->getStateMachine();
	auto newScene = sceneToSwap;

	if (sceneChangeMode != SceneMode::REMOVE) {

		if (sceneChangeMode == SceneMode::OVERRIDE) {
			states->popState();
		}
		else if (sceneChangeMode == SceneMode::SINGLE) {
			while (!states->empty()) {
				states->popState();
			}
		}

		states->pushState(newScene);
		newScene->init();
	}
	else {
		states->popState();
		states->currentState()->init();
	}
	shouldSwap = false;
	sceneToSwap = nullptr;
}
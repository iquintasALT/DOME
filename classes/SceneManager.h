#pragma once


class Game;
class GameScene;
class SceneManager
{
public:
	
	enum class SceneMode
	{
		ADDITIVE, SINGLE, OVERRIDE, REMOVE
	};

	inline SceneManager(Game* game) : game(game), sceneToSwap(nullptr), shouldSwap(false), sceneChangeMode(SceneMode::ADDITIVE){};
	
	
	
	void ChangeScene(GameScene* scene, SceneMode mode);

	/// <summary>
	/// THIS METHOD SHOULD ONLY BE CALLED BY THE MANAGER!
	/// </summary>
	void LoadScene(); 
	operator bool() const;
private:
	Game* game;

	bool shouldSwap;
	SceneMode sceneChangeMode;
	GameScene* sceneToSwap;
};


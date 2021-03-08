#include "./game/Game.h"

int main(int a, char* argv[])
{
	Game* game = new Game();
	game->mainLoop();

	delete game;
	return 0;
}
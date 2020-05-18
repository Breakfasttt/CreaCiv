//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : Main
//*******************

#include "Game.hpp"


int main()
{
	srand(time(NULL));
	Game MainGame;

	MainGame.init();
	MainGame.update();
	MainGame.deinit();

	return 0;
}
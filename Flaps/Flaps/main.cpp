#include<SFML/Graphics.hpp>
#include<Globals.h>
#include"Game.h"

int main() 
{

	sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Flappy bird clone");
	Game game(win);
	//idk looks clean


	game.startGameLoop();
	return 0;
}
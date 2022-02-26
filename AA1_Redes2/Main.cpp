#include <iostream>
#include <SFML/Network.hpp>

#include "Game.h"

int main()
{
	srand((unsigned int)time(NULL));

	Game* game = new Game();

	std::string type;
	while (type != "e")
	{
		std::cin >> type;
		std::cout << std::endl;
	}

	return 0;
}
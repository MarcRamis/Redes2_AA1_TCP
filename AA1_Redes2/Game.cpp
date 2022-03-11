#include "Game.h"

Game::Game()
{
	maze = new Maze();

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		Player* p = new Player;
		p->hand = maze->DealCards(CARDS_TO_DEAL);

		players.push_back(p);
	}
	int counter = 0;

	for (Player *p : players)
	{
		std::cout << "Player " << counter + 1 << ": ";
		for (Card* c : p->hand)
		{
			c->Draw();
		}
		counter++;
		std::cout << std::endl;
	}
}

void Game::Update()
{
}

void Game::Draw()
{
}

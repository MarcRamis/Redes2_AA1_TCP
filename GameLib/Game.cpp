#include "Game.h"

void Game::LoopGame(std::vector<TcpSocket*>* _clientes, Player player)
{
	{
		for (int i = 0; i < _clientes->size() + 1; i++)
		{
			if (i == player.idTurn)
			{
			}
			else
			{
			}
		}
	}
}

void Game::StartGame(std::vector<TcpSocket*>* _clientes, Player player)
{
	ConsoleClear();
	std::cout << "DEALING CARDS" << std::endl;
	ConsoleWait(2000.f);

	srand(player.randomSeed);

	player.maze = new Maze();

	std::cout << "I am player number: " << player.idTurn + 1 << std::endl;

	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		//std::cout << i + 1 << "  ";
		if (i == player.idTurn)
		{
			//std::cout << "My cards: " << std::endl;
			player.hand = player.maze->DealCards(CARDS_TO_DEAL);
			for (Card* c : player.hand)
			{
				c->Draw();
			}
			std::cout << std::endl;
		}
		else
		{
			std::vector<Card*> cards = player.maze->DealCards(CARDS_TO_DEAL);
			player.otherhands.push_back(&cards);

			//std::cout << "Other player cards: " << std::endl;
			//for (auto c : player.otherhands)
			//{
			//	for (auto c2 : *c)
			//	{
			//		c2->Draw();
			//	}
			//}
			//std::cout << std::endl;
		}
	}

	LoopGame(_clientes, player);
}
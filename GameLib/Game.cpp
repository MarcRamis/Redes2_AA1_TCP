#include "Game.h"

void Game::LoopGame(std::vector<TcpSocket*>* _clientes, Player player)
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

void Game::DrawGame(std::vector<TcpSocket*>* _clientes, Player player)
{
	std::cout << "I am player number: " << player.idTurn + 1 << std::endl;
	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		//std::cout << i + 1 << "  ";
		if (i == player.idTurn)
		{
			//std::cout << "My cards: " << std::endl;
			for (Card* c : player.hand)
			{
				c->Draw();
			}
			std::cout << std::endl;
		}
		else
		{

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
}

void Game::SetTurn(std::vector<TcpSocket*>* _clientes, Player player)
{
	int tmpTurn = player.idTurn;
	int *counter = new int[_clientes->size() + 1];

	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		if (i == tmpTurn)
		{
			for (Card *c : player.hand)
			{
				if (c->cardType == Card::EType::ORGAN)
				{
					counter[i]++;
				}
			}
		}
		else
		{
			for (auto c : player.otherhands)
			{
				for (auto c2 : *c)
				{
					if (c2->cardType == Card::EType::ORGAN)
					{
						counter[i]++;
					}
				}
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

	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		//std::cout << i + 1 << "  ";
		if (i == player.idTurn)
		{
			//std::cout << "My cards: " << std::endl;
			player.hand = player.maze->DealCards(CARDS_TO_DEAL);
		}
		else
		{
			//std::cout << "Other player cards: " << std::endl;
			std::vector<Card*> cards = player.maze->DealCards(CARDS_TO_DEAL);
			player.otherhands.push_back(&cards);
		}
	
	SetTurn(_clientes, player);
	DrawGame(_clientes, player);
	//LoopGame(_clientes, player);
}
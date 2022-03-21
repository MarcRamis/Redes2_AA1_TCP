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
			std::cout << "My cards: " << std::endl;
			for (Card* c : player.hand)
			{
				c->Draw();
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Other player cards: " << std::endl;
			for (auto c : player.otherhands)
			{
				for (auto c2 : *c)
				{
					c2->Draw();
				}
			}
			std::cout << std::endl;
		}
	}
}

void Game::SetTurn(std::vector<TcpSocket*>* _clientes, Player player)
{
	std::vector<int> ammountOrgans(_clientes->size() + 1);
	
	// Count number of organs every player has
	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		if (i == player.idTurn)
		{
			for (Card* c : player.hand)
			{
				if (c->cardType == Card::EType::ORGAN)
				{
					ammountOrgans.at(i)++;
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
						ammountOrgans.at(i)++;
					}
				}
			}
		}
	}

	//std::cout << "My Organs: " << ammountOrgans.at(player.idTurn) << std::endl;
	//ammountOrgans.erase(ammountOrgans.begin() + player.idTurn);
	
	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		std::cout << i + 1 << " : Organs: " << ammountOrgans.at(i) << std::endl;
	}
	
	//int ammount = ammountOrgans.at(player.idTurn);
	//// Me make a reverse loop because we want the first player to be the first one if there is draw in organ cards
	//for (int i = 0; i < ammountOrgans.size() + 1; i++)
	//{
	//	if (ammount >= ammountOrgans.at(i))
	//	{
	//		player.idTurn = i;
	//	}
	//	else
	//	{
	//		player.idOtherTurns.at(i) = i;
	//	}
	//}
	//
	//std::cout << "My turn: " << player.idTurn;
	//for (int i = 0; i < player.idOtherTurns.size() ; i++)
	//{
	//	std::cout << " | Other turn: " << player.idOtherTurns.at(i) << std::endl;
	//}
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
			player.idOtherTurns.push_back(i); // Add turns from the other players
			std::vector<Card*> cards = player.maze->DealCards(CARDS_TO_DEAL);
			player.otherhands.push_back(&cards);
		}
	}
	SetTurn(_clientes, player);
	DrawGame(_clientes, player);
	//LoopGame(_clientes, player);
}
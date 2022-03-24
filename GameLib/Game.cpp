#include "Game.h"

void Game::LoopGame(std::vector<TcpSocket*>* _clientes, Player &player)
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

void Game::DrawGame(std::vector<TcpSocket*>* _clientes, Player &player)
{
	std::cout << "I am player number: " << player.idTurn + 1 << std::endl << std::endl;
	
	std::cout << "My cards: " << std::endl;
	for (Card* c : player.hand)
	{
		c->Draw();
	}
	std::cout << std::endl;
	
	for (auto c : player.otherhands)
	{
		std::cout << "Other player cards: " << std::endl;
		for (auto c2 : c)
		{
			c2->Draw();
		}
		std::cout << std::endl;
	}

	
}

void Game::SetTurn(std::vector<TcpSocket*>* _clientes, Player &player)
{
	int myAmmount = 0;
	int tmpAmmount = 0;
	std::vector<std::pair<int,int>> ammountOrgans; // vector where organs counter of every other player are stored
	std::priority_queue<std::pair<int, int> > turnOrgans;
	
	std::cout << "My initial turn: " << player.idTurn + 1 << std::endl;
	
	// SUMM ORGANS
	for (Card* c : player.hand)
	{
		if (c->cardType == Card::EType::ORGAN)
		{
			tmpAmmount++;
		}
	}
	ammountOrgans.push_back(std::pair<int,int>(tmpAmmount,player.idTurn));
	tmpAmmount = 0;
	// Count number of organs every other player has
	for (int i = 0; i < player.otherhands.size(); i++)
	{
		for (int j = 0; j < player.otherhands.at(i).size(); j++)
		{
			if (player.otherhands.at(i).at(j)->cardType == Card::EType::ORGAN)
			{
				tmpAmmount++;
			}
		}

		ammountOrgans.push_back(std::pair<int, int>(tmpAmmount, player.idOtherTurns.at(i)));
		//ammountOrgans.push_back(tmpAmmount);
		tmpAmmount = 0;
	}
	
	ammountOrgans.size();

	// Me make a reverse loop because we want the first player to be the first one if there is draw in organ cards
	// Ordered by the first one & for max number of organs
	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		turnOrgans.push(std::pair<int, int>(ammountOrgans.at(i).first, ammountOrgans.at(i).second));
	}
	
	std::vector<std::pair<int, int>> containerTurnOrgans;
	
	while (!turnOrgans.empty()) {
		std::cout << turnOrgans.top().first
			<< " " << turnOrgans.top().second + 1
			<< std::endl;
		containerTurnOrgans.push_back(std::pair<int,int>(turnOrgans.top().first, turnOrgans.top().second));
		turnOrgans.pop();
	}
	for (int i = 0; i < containerTurnOrgans.size(); i++)
	{
		if (containerTurnOrgans.at(i).second == player.idTurn)
		{	
			player.idTurn = i;
			break;
		}
	}


	//std::cout << "My ammount of organs: " << myAmmount << std::endl;
	//for (int i = 0; i < _clientes->size() + 1; i++)
	//{
	//	std::cout << "Client "<< i + 1 << " has " << otherAmmountOrgans.at(i) << " Organs "<< std::endl;
	//}
	//std::cout << std::endl;
	
	
	
	
	
	// set turn
	//for (int i = 0; i < _clientes->size() + 1; i++)
	//{
	//	if (myAmmount >= otherAmmountOrgans.at(i))
	//	{
	//		std::cout << "true then my turn is updated to that turn" << std::endl;
	//		player.idTurn = i;
	//		std::cout << "Now my turn is: " << player.idTurn << std::endl;
	//	}
	//	else {
	//		std::cout << "false do nothing" << std::endl;
	//	}
	//	
	//	std::cout << std::endl;
	//}
}

void Game::StartGame(std::vector<TcpSocket*>* _clientes, Player &player)
{;
	ConsoleClear();
	std::cout << "DEALING CARDS" << std::endl << std::endl;
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
			player.otherhands.push_back(cards);
		}
	}
	SetTurn(_clientes, player);
	DrawGame(_clientes, player);
	//LoopGame(_clientes, player);
}
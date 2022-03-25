#include "Game.h"

void Game::LoopGame(std::vector<TcpSocket*>* _clientes, Player& player)
{
	while (_clientes->size() != 0 && !WinCondition(_clientes, player))
	{
		if (gameTurn == player.idTurn)
		{
			canChat = false;
			PlayCard(_clientes, player);
		}
		else
		{
			canChat = true;
		}
	}

	if (_clientes->size() == 0)
	{
		std::cout << "The game has finished. " << std::endl;
	}
}

void Game::DrawGame(std::vector<TcpSocket*>* _clientes, Player& player)
{
	ConsoleClear();

	// HUD --> (NAME ID + TURN)
	// Draw me
	ConsoleXY(0, 0);
	ConsoleSetColor(ConsoleColor::DARKGREEN, ConsoleColor::BLACK);
	std::cout << localPort << " | " << player.idTurn + 1 << std::endl;
	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);

	// Player game turn
	ConsoleXY(HUD_MAX_POS_GAME_X / 2, HUD_MAX_POS_GAME_Y / 2);
	std::cout << " Player Turn: ";
	ConsoleXY((HUD_MAX_POS_GAME_X / 2) - 1, (HUD_MAX_POS_GAME_Y / 2) + 1);
	if (gameTurn == player.idTurn)
	{
		std::cout << " [ " << localPort << " | " << gameTurn + 1 << " ] " << std::endl;
	}
	else
	{
		for (int i = 0; i < _clientes->size(); i++)
		{
			if (gameTurn == player.idOtherTurns.at(i))
			{
				std::cout << " [ " << _clientes->at(i)->GetRemotePort().port << " | " << gameTurn + 1 << " ] " << std::endl;
				break;
			}
		}
	}

	// Draw other players
	for (int i = 0; i < _clientes->size(); i++)
	{
		if (i == 0)
		{
			ConsoleXY(HUD_MAX_POS_GAME_X, 0);
			ConsoleSetColor(ConsoleColor::DARKRED, ConsoleColor::BLACK);
		}
		else if (i == 1)
		{
			ConsoleXY(0, HUD_MAX_POS_GAME_Y);
			ConsoleSetColor(ConsoleColor::DARKRED, ConsoleColor::BLACK);
		}
		else if (i == 2)
		{
			ConsoleXY(HUD_MAX_POS_GAME_X, HUD_MAX_POS_GAME_Y);
			ConsoleSetColor(ConsoleColor::DARKRED, ConsoleColor::BLACK);
		}
		std::cout << _clientes->at(i)->GetRemotePort().port << " | " << player.idOtherTurns.at(i) + 1 << std::endl;
		ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	}

	// HUD --> (PLAYER CARDS)
	// Draw this played cards
	ConsoleXY(0, 1);
	for (Card* c : player.playedCards)
	{
		c->Draw();
		std::cout << std::endl;
	}

	// Draw other played cards
	for (int i = 0; i < player.otherPlayedCards.size(); i++)
	{
		for (int j = 0; j < player.otherPlayedCards.at(i).size(); j++)
		{
			if (i == 0)
			{
				ConsoleXY(HUD_MAX_POS_GAME_X, 1);
			}
			else if (i == 1)
			{
				ConsoleXY(0, HUD_MAX_POS_GAME_Y - 1);
			}
			else if (i == 2)
			{
				ConsoleXY(HUD_MAX_POS_GAME_X, HUD_MAX_POS_GAME_Y - 1);
			}
			player.otherPlayedCards.at(i).at(j)->Draw();
			std::cout << std::endl;
		}
	}

	// HUD --> (MY CARDS)
	ConsoleXY(0, HUD_MAX_POS_GAME_Y + 2);
	std::cout << "My hand: " << std::endl;
	for (Card* c : player.hand)
	{
		c->Draw();
	}
	std::cout << std::endl << std::endl;

	for (auto c : player.otherhands)
	{
		std::cout << "Other hands: " << std::endl;
		for (auto c2 : c)
		{
			c2->Draw();
		}
		std::cout << std::endl;
	}
}

void Game::PlayCard(std::vector<TcpSocket*>* _clientes, Player& player)
{
	bool endTurn = true;
	Card *tmpCard = new Card();
	int selection = 0;

	while (endTurn)
	{
		selection = 0;
		do {
			std::cout << "Use one of your cards: ( 1 - 3 ) or Discard ( 4 )" << std::endl;
			std::cin >> selection;
		} while (selection > 4 || selection < 1);

		// Play cards
		if (selection <= 3 && selection >= 1)
		{
			tmpCard = player.hand.at(selection - 1);

			switch (player.hand.at(selection - 1)->cardType)
			{
			case Card::EType::ORGAN:
				player.hand.at(selection - 1)->Play(player, nullptr, selection - 1);
				break;
			case Card::EType::MEDICINE:
				break;
			case Card::EType::TREATMENT:
				break;
			case Card::EType::VIRUS:
				break;
			default:
				break;
			}

			if (!player.hand.at(selection - 1)->endTurn)
			{
				std::cout << "This card is already played" << std::endl;
			}
			else
			{

				endTurn = !endTurn;
			}

			if (gameTurn != _clientes->size()) gameTurn++;
			else gameTurn = 0;
		}
		else // Discard cards
		{
			// discard

			endTurn = !endTurn;
		}
	
	}

	// SEND PROTOCOOL
	switch (player.hand.at(selection - 1)->cardType)
	{
	case Card::EType::ORGAN:
		Protocol::Peer::SendPlayOrgan(_clientes, player.id, selection - 1);
		break;
	case Card::EType::MEDICINE:
		break;
	case Card::EType::TREATMENT:
		break;
	case Card::EType::VIRUS:
		break;
	default:
		break;
	}
	
	DrawGame(_clientes, player);
}

void Game::SetTurn(std::vector<TcpSocket*>* _clientes, Player& player)
{
	int myAmmount = 0;
	int tmpAmmount = 0;
	std::vector<std::pair<int, int>> ammountOrgans; // vector where organs counter of every other player are stored
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
	ammountOrgans.push_back(std::pair<int, int>(tmpAmmount, player.idTurn));
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
		containerTurnOrgans.push_back(std::pair<int, int>(turnOrgans.top().first, turnOrgans.top().second));
		turnOrgans.pop();
	}

	// New turn for this player
	for (int i = 0; i < containerTurnOrgans.size(); i++)
	{
		if (containerTurnOrgans.at(i).second == player.idTurn)
		{
			player.idTurn = i;
			break;
		}
	}
	// Know new turns for other players
	std::vector<int>tmpOtherTurns = player.idOtherTurns;

	for (int i = 0; i < containerTurnOrgans.size(); i++)
	{
		for (int j = 0; j < player.idOtherTurns.size(); j++)
		{
			if (containerTurnOrgans.at(i).second == tmpOtherTurns.at(j))
			{
				player.idOtherTurns.at(j) = i;
				break;
			}
		}
	}

	ConsoleWait(1000.f);
}

bool Game::WinCondition(std::vector<TcpSocket*>* _clientes, Player& player)
{
	// Check if this player has won
	int tmpAmmount = 0;
	for (Card* c : player.playedCards)
	{
		if (c->cardType == Card::EType::ORGAN && c->state != Card::EOrganState::INFECTED)
		{
			tmpAmmount++;
		}
	}
	if (tmpAmmount == 4)
	{
		playerIdThatWon = player.id;
		std::cout << "yo he ganado" << std::endl;
		return true;
	}
	else
	{
		tmpAmmount = 0;

		// Check if other players have won
		for (int i = 0; i < player.otherPlayedCards.size(); i++)
		{
			for (int j = 0; j < player.otherPlayedCards.at(i).size(); j++)
			{
				if (player.otherPlayedCards.at(i).at(j)->cardType == Card::EType::ORGAN && player.otherPlayedCards.at(i).at(j)->state != Card::EOrganState::INFECTED)
				{
					tmpAmmount++;
				}
			}
			if (tmpAmmount == 4)
			{
				playerIdThatWon = player.idOtherPlayers.at(i);
				std::cout << "alguien ha ganado" << std::endl;
				return true;
			}
		}
	}

	return false;
}

void Game::StartGame(std::vector<TcpSocket*>* _clientes, Player& player)
{
	ConsoleClear();
	std::cout << "DEALING CARDS" << std::endl << std::endl;
	ConsoleWait(1000.f);

	srand(player.randomSeed);

	player.maze = new Maze();
	
	// DEAL INITIAL CARDS
	for (int i = 0; i < _clientes->size() + 1; i++)
	{
		if (i == player.idTurn)
		{
			player.id = i; // save this player initial id
			player.hand = player.maze->DealCards(CARDS_TO_DEAL);
		}
		else
		{
			player.idOtherPlayers.push_back(i); // save other players initial id
			player.idOtherTurns.push_back(i); // Add turns from the other players
			std::vector<Card*> cards = player.maze->DealCards(CARDS_TO_DEAL);
			player.otherhands.push_back(cards);
		}
	}
	
	SetTurn(_clientes, player); // SET NEW TURN
	DrawGame(_clientes, player);
	
	// UPDATE - LOOP GAME
	LoopGame(_clientes, player);
}
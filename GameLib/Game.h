#pragma once

#include <vector>
#include <stack>
#include <queue>

#include "TcpSocket.h"
#include "Player.h"
#include "Protocol.h"

class Game
{
public:
	int playerIdThatWon;
	
	int gameTurn;
	bool canChat;
	bool gameStart;
	std::vector<bool> gameReady;
	std::string gameName;
	unsigned short localPort;
	
	void StartGame(std::vector<TcpSocket*>* _clientes, Player &player);
	void LoopGame(std::vector<TcpSocket*>* _clientes, Player &player);
	void DrawGame(std::vector<TcpSocket*>* _clientes, Player &player);

	void SetTurn(std::vector<TcpSocket*>* _clientes, Player &player);
	bool WinCondition(std::vector<TcpSocket*>* _clientes, Player& player);
	bool CorrectIdCardInTable(int selection, Player& player);
	void NextTurn(std::vector<TcpSocket*>* _clientes, Player& player);
	void PlayCard(std::vector<TcpSocket*>* _clientes, Player& player);
	void PlayerDisconnected(std::vector<TcpSocket*>* _clientes, Player& player, int i);
	
	int GetIDFromSelectedPlayer(Player& player, int selection);
	int GetIDFromSelectedCard(Player& player, int selection);
};
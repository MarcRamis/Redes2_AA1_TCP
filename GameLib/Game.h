#pragma once

#include <vector>
#include <queue>
#include "TcpSocket.h"
#include "Player.h"

class Game
{
	int gameTurn;
	
	void SetTurn(std::vector<TcpSocket*>* _clientes, Player &player);
public:
	bool canChat;
	bool gameStart;
	std::vector<bool> gameReady;
	std::string gameName;
	
	void StartGame(std::vector<TcpSocket*>* _clientes, Player &player);
	void LoopGame(std::vector<TcpSocket*>* _clientes, Player &player);

	void DrawGame(std::vector<TcpSocket*>* _clientes, Player &player);
};
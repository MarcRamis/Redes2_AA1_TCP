#pragma once

#include <vector>
#include "TcpSocket.h"
#include "Player.h"

class Game
{
	void SetTurn(std::vector<TcpSocket*>* _clientes, Player player);
public:

	void StartGame(std::vector<TcpSocket*>* _clientes, Player player);
	void LoopGame(std::vector<TcpSocket*>* _clientes, Player player);

	void DrawGame(std::vector<TcpSocket*>* _clientes, Player player);
};
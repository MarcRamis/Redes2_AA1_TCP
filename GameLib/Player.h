#pragma once
#include <vector>
#include "Card.h"
#include "Maze.h"

class Player
{
public:
	
	unsigned int randomSeed;
	
	// id
	int id;
	std::vector<int> idOtherPlayers;
	
	// game turn
	int idTurn;
	std::vector<int> idOtherTurns;
	
	// card games variables
	std::vector<Card*> hand;
	std::vector<std::vector<Card*>> otherhands;
	
	// played cards
	std::vector<Card*> playedCards;
	std::vector<std::vector<Card*>> otherPlayedCards;
	
	// maze
	Maze* maze;

	Player();
	~Player();
};
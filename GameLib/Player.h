#pragma once
#include <vector>
#include "Card.h"
#include "Maze.h"

class Player
{
public:
	
	unsigned int randomSeed;
	
	// game turn
	int idTurn;
	std::vector<int> idOtherTurns;
	
	// card games variables
	std::vector<Card*> hand;
	std::vector<std::vector<Card*>> otherhands;
	
	std::vector<Card*> playedCards;
	std::vector<std::vector<Card*>> otherPlayedCards;
	
	Maze* maze;

	Player();
	~Player();
};
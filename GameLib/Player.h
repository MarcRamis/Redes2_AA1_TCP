#pragma once
#include <vector>
#include "Card.h"
#include "Maze.h"

class Player
{
public:
	
	// card games variables
	unsigned int randomSeed;
	
	std::vector<Card*> hand;
	std::vector<std::vector<Card*>*> otherhands;

	std::vector<Card*> playedCards;
	std::vector<std::vector<Card*>*> otherPlayedCards;
	
	Maze* maze;

	Player();
	~Player();
};
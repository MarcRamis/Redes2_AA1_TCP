#pragma once
#include <vector>
#include "Card.h"
#include "Maze.h"

class Player
{
public:
	
	// card games variables
	std::vector<Card*> hand;
	unsigned int randomSeed;
	Maze* maze;

	Player();
	~Player();
};
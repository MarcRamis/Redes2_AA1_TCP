#pragma once
#include <vector>
#include "Card.h"

class Player
{
public:
	std::vector<Card*> hand;

	Player();
	~Player();
};
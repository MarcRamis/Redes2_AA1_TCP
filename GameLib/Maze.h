#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>

#include "Card.h"
#include "Constants.h"

class Maze
{
public:
	std::stack<Card*> deck;
	std::stack<Card*> discardDeck;
	std::vector<Card*> playedCards;

	Maze();
	std::vector<Card*> DealCards(unsigned int maxCardsToDeal);
};
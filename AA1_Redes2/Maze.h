#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>

#include "Card.h"



class Maze
{
public:
	std::stack<Card*> deck;
	std::stack<Card*> discardDeck;

	Maze();
};
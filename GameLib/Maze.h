#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>

#include "Card.h"
#include "Constants.h"

class Organ;
class Medicine;
class Virus;
class Treatment;

class Maze
{
public:
	std::stack<Card*> deck;
	std::stack<Card*> discardDeck;
	
	Maze();
	std::vector<Card*> DealCards(unsigned int maxCardsToDeal);
	void FillDeck(std::vector<Card*> deck);
};
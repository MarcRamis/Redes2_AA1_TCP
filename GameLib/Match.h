#pragma once
#include <string>
#include <vector>

#include "Port.h"
#include "Player.h"

class Match
{	
public:
	
	// Choosing variables
	std::string name;
	std::string pw;
	
	int maxPlayers; // (2-4)
	std::vector<Port> ports;
	
	float timeStamp;

	Match();
	~Match();
};
#pragma once
#include <string>
#include <vector>
#include "Port.h"

class Match
{	
public:

	// Choosing
	std::string name;
	std::string pw;
	
	int maxPlayers; // (2-4)
	std::vector<Port> currentPlayers;
	
	float timeStamp;
	
	Match();
	~Match();
};
#pragma once

#include <iostream>
#include <vector>
#include "ConsoleControl.h"

class Player;

class Card
{
public:
	
	bool endTurn = true;

	enum class EType { NONE, ORGAN, MEDICINE, VIRUS, TREATMENT };
	EType cardType;

	enum class EOrganState { NONE, IMMUNIZED, VACUNATED, INFECTED };
	EOrganState state = EOrganState::NONE;
	
	Card();
	~Card();
	
	virtual void Draw();
	virtual void Play(Player& p, Card* cardToEffect, int id/*, std::vector<Card*> containerToPush, std::vector<Card*> containerToErase*/);
};
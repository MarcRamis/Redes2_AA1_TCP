#pragma once

#include <iostream>
#include "ConsoleControl.h"

class Card
{
public:

	Card();
	~Card();
	
	virtual void Draw() = 0;
	virtual void ImmunizeOrgan();
	virtual void VacunateOrgan();
	virtual void InfectateOrgan();
};
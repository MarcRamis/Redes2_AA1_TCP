#pragma once
#include "Card.h"
class Virus : public Card
{
public:
	enum class EVirusType { VIRUSJOKER, VIRUSHEART, VIRUSSTOMACH, VIRUSBRAIN, VIRUSBONE };
	EVirusType type;

	Virus();
	Virus(EVirusType _type);

	void Draw();
};


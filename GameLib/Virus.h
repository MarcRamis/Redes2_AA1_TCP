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
	void Play(Player& p, Card* cardToEffect, int id/*, std::vector<Card*> containerToPush, std::vector<Card*> containerToErase*/);
};


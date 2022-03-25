#include "Virus.h"

Virus::Virus()
{
}

Virus::Virus(EVirusType _type) : type(_type) { cardType = EType::VIRUS; }

void Virus::Draw()
{
	switch (type)
	{
	case Virus::EVirusType::VIRUSJOKER:
		ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::BLACK);
		std::cout << "Virus - Joker | ";
		break;
	case Virus::EVirusType::VIRUSHEART:
		ConsoleSetColor(ConsoleColor::RED, ConsoleColor::BLACK);
		std::cout << "Virus - Heart | ";
		break;
	case Virus::EVirusType::VIRUSSTOMACH:
		ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::BLACK);
		std::cout << "Virus - Stomach | ";
		break;
	case Virus::EVirusType::VIRUSBRAIN:
		ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::BLACK);
		std::cout << "Virus - Brain | ";
		break;
	case Virus::EVirusType::VIRUSBONE:
		ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::BLACK);
		std::cout << "Virus - Bone | ";
		break;
	default:
		break;
	}

	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Virus::Play(Player& p, Card* cardToEffect, int id/*, std::vector<Card*> containerToPush, std::vector<Card*> containerToErase*/)
{
}

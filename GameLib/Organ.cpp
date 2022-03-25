#include "Organ.h"

#include "Player.h"

Organ::Organ()
{
}

Organ::Organ(EOrganType _type) : type(_type) { cardType = EType::ORGAN; };

void Organ::Draw()
{
	switch (type)
	{
	case Organ::EOrganType::JOKER:
		ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::BLACK);
		std::cout << "Organ - Joker | ";
		break;
	case Organ::EOrganType::HEART:
		ConsoleSetColor(ConsoleColor::RED, ConsoleColor::BLACK);
		std::cout << "Organ - Heart | ";
		break;
	case Organ::EOrganType::STOMACH:
		ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::BLACK);
		std::cout << "Organ - Stomach | ";
		break;
	case Organ::EOrganType::BRAIN:
		ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::BLACK);
		std::cout << "Organ - Brain | ";
		break;
	case Organ::EOrganType::BONE:
		ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::BLACK);
		std::cout << "Organ - Bone | ";
		break;
	default:
		break;
	}

	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Organ::Play(Player& p, Card* cardToEffect, int id)
{
	bool pushOnce = true;
	
	for (int i = 0; i < p.playedCards.size(); i++)
	{
		// this is done because we need to look at every played cards and if the first one is different but the second isn't it will push anyways on first iteration
		if (this->type == GetType(dynamic_cast<Organ*>(p.playedCards.at(i))))
		{
			pushOnce = false;
			break;
		}
	}
	// so if some card is not the same we push back to played cards
	if (pushOnce)
	{
		p.playedCards.push_back(this);
		p.hand.erase(p.hand.begin() + id);
	}
	else
	{
		endTurn = false;
	}
}

Organ::EOrganType Organ::GetType(Organ* organ)
{
	return organ->type;
}

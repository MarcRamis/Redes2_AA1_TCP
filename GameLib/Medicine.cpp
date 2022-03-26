#include "Medicine.h"

#include "Player.h"

Medicine::Medicine()
{
}

Medicine::Medicine(EMedicineType _type) : type(_type) { cardType = EType::MEDICINE; }

void Medicine::Draw()
{
	switch (type)
	{
	case Medicine::EMedicineType::MEDICINEJOKER:
		ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::BLACK);
		std::cout << "Medicine - Joker | ";
		break;
	case Medicine::EMedicineType::MEDICINEHEART:
		ConsoleSetColor(ConsoleColor::RED, ConsoleColor::BLACK);
		std::cout << "Medicine - Heart | ";
		break;
	case Medicine::EMedicineType::MEDICINESTOMACH:
		ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::BLACK);
		std::cout << "Medicine - Stomach | ";
		break;
	case Medicine::EMedicineType::MEDICINEBRAIN:
		ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::BLACK);
		std::cout << "Medicine - Brain | ";
		break;
	case Medicine::EMedicineType::MEDICINEBONE:
		ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::BLACK);
		std::cout << "Medicine - Bone | ";
		break;
	default:
		break;
	}

	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Medicine::Play(Player& p, Card* cardToEffect, int id)
{
}

void Medicine::VacunateOrgan(Player& p, int idCardToAffect, int id)
{
	// Vacunate the card
	// If it was vacunated before, then immunize
	if (p.playedCards.at(idCardToAffect)->state == Card::EOrganState::VACUNATED) {
		p.playedCards.at(idCardToAffect)->state = Card::EOrganState::IMMUNIZED; // immunize card
	}
	else
	{
		p.playedCards.at(idCardToAffect)->state = Card::EOrganState::VACUNATED; // vacunate card
	}

	// DISCARD THE CARD USED
	// Add to discard cards
	p.maze->discardDeck.push(this);
	// Delete from the hand
	p.hand.erase(p.hand.begin() + id);
	// Draw new card
	std::vector<Card*> tmpCards = p.maze->DealCards(1);
	for (Card* c : tmpCards)
	{
		p.hand.push_back(c);
		std::cout << "You drawn: "; c->Draw(); std::cout << std::endl;
	}
}

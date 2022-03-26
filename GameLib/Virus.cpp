#include "Virus.h"
#include "Player.h"

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

void Virus::Play(Player& p, Card* cardToEffect, int id)
{

}

void Virus::InfectOrgan(Player& p, int playerToAffect, int idCardToAffect, int id)
{
	// Infect the card
	// If it was infected before, then dies
	if (p.otherPlayedCards.at(playerToAffect).at(idCardToAffect)->state != Card::EOrganState::IMMUNIZED)
	{
		if (p.otherPlayedCards.at(playerToAffect).at(idCardToAffect)->state == Card::EOrganState::INFECTED) {
			p.maze->discardDeck.push(p.otherPlayedCards.at(playerToAffect).at(idCardToAffect)); // This add the card to the discard deck
			p.otherPlayedCards.at(playerToAffect).erase(p.otherPlayedCards.at(playerToAffect).begin() + idCardToAffect); // This deletes the card from the table
		}
		else
		{
			p.otherPlayedCards.at(playerToAffect).at(idCardToAffect)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
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
}

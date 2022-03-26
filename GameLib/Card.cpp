#include "Card.h"
#include "Player.h"
#include "Organ.h"
#include "Virus.h"
#include "Medicine.h"
#include "Treatment.h"

void Card::Draw()
{
}

void Card::Play(Player& p, Card* cardToEffect, int id)
{

}

void Card::InfectOrgan(Player& p, int playerToAffect, int idCardToAffect, int id)
{
}

void Card::VacunateOrgan(Player& p, int idCardToAffect, int id)
{
}

Organ* Card::GetOrganCard()
{
    return dynamic_cast<Organ*>(this);
}

Card::Card()
{
}

Card::~Card()
{
}

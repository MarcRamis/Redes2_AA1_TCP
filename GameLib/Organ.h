#pragma once
#include "Card.h"
class Organ : public Card
{
public:
	enum class EOrganType { JOKER, HEART, STOMACH, BRAIN, BONE };
	EOrganType type;

	enum class EOrganState { NONE, IMMUNIZED, VACUNATED, INFECTED };
	EOrganState state = EOrganState::NONE;

	Organ();
	Organ(EOrganType _type);

	void Draw();
	

	void ImmunizeOrgan();
	void VacunateOrgan();
	void InfectateOrgan();
};


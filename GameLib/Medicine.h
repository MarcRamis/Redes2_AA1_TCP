#pragma once
#include "Card.h"
class Medicine : public Card
{
public:
	enum class EMedicineType { MEDICINEJOKER, MEDICINEHEART, MEDICINESTOMACH, MEDICINEBRAIN, MEDICINEBONE };
	EMedicineType type;

	Medicine();
	Medicine(EMedicineType _type);

	void Draw();
	void Play(Player& p, Card* cardToEffect, int id);
	void VacunateOrgan(Player& p, int idCardToAffect, int id);
};
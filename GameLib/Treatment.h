#pragma once
#include "Card.h"
class Treatment : public Card
{
public:
	enum class ETreatmentType { INFECTION, ORGANTHIEF, TRASPLANT, LATEXGLOVE, MEDICALERROR };
	ETreatmentType type;

	Treatment();
	Treatment(ETreatmentType _type);

	void Draw();
	void Play(Player& p, Card* cardToEffect, int id);
	void PlayLatexGlove(Player &p, int id);
	void PlayTrasplant(Player& p, int id, int selfOrgan, int otherOrgan);
};
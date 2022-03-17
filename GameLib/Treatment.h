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
};
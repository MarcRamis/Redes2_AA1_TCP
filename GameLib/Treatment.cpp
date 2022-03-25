#include "Treatment.h"

Treatment::Treatment()
{
}

Treatment::Treatment(ETreatmentType _type) : type(_type) { cardType = EType::TREATMENT; };

void Treatment::Draw()
{
	{
		switch (type)
		{
		case Treatment::ETreatmentType::INFECTION:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::BLACK);
			std::cout << "Treatment - Infection | ";
			break;
		case Treatment::ETreatmentType::ORGANTHIEF:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::BLACK);
			std::cout << "Treatment - Organ Thief | ";
			break;
		case Treatment::ETreatmentType::TRASPLANT:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::BLACK);
			std::cout << "Treatment - Trasplant | ";
			break;
		case Treatment::ETreatmentType::LATEXGLOVE:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::BLACK);
			std::cout << "Treatment - Latex glove | ";
			break;
		case Treatment::ETreatmentType::MEDICALERROR:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::BLACK);
			std::cout << "Treatment - Medical error | ";
			break;
		default:
			break;
		}

		ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	}
}

void Treatment::Play(Player& p, Card* cardToEffect, int id)
{
}


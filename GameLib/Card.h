#pragma once

#include <iostream>
#include "ConsoleControl.h"

class Card
{
public:

	Card();
	~Card();
	
	virtual void Draw();
};

class Organ : public Card
{
public:
	enum class EOrganType { JOKER, HEART, STOMACH, BRAIN, BONE};
	EOrganType type;

	Organ() {};
	Organ(EOrganType _type) : type(_type) {};

	void Draw()
	{
		switch (type)
		{
		case Organ::EOrganType::JOKER:
			ConsoleSetColor(ConsoleColor::MAGENTA,ConsoleColor::WHITE);
			std::cout << "Organ - Joker | ";
			break;
		case Organ::EOrganType::HEART:
			ConsoleSetColor(ConsoleColor::RED, ConsoleColor::WHITE);
			std::cout << "Organ - Heart | ";
			break;
		case Organ::EOrganType::STOMACH:
			ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::WHITE);
			std::cout << "Organ - Stomach | ";
			break;
		case Organ::EOrganType::BRAIN:
			ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::WHITE);
			std::cout << "Organ - Brain | ";
			break;
		case Organ::EOrganType::BONE:
			ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::WHITE);
			std::cout << "Organ - Bone | ";
			break;
		default:
			break;
		}
	}
};

class Virus : public Card
{
public:
	enum class EVirusType { VIRUSJOKER, VIRUSHEART, VIRUSSTOMACH, VIRUSBRAIN, VIRUSBONE };
	EVirusType type;

	Virus() {};
	Virus(EVirusType _type) : type(_type) {};

	void Draw()
	{
		switch (type)
		{
		case Virus::EVirusType::VIRUSJOKER:
			ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::WHITE);
			std::cout << "Virus - Joker | ";
			break;
		case Virus::EVirusType::VIRUSHEART:
			ConsoleSetColor(ConsoleColor::RED, ConsoleColor::WHITE);
			std::cout << "Virus - Heart | ";
			break;
		case Virus::EVirusType::VIRUSSTOMACH:
			ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::WHITE);
			std::cout << "Virus - Stomach | ";
			break;
		case Virus::EVirusType::VIRUSBRAIN:
			ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::WHITE);
			std::cout << "Virus - Brain | ";
			break;
		case Virus::EVirusType::VIRUSBONE:
			ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::WHITE);
			std::cout << "Virus - Bone | ";
			break;
		default:
			break;
		}
	}
};

class Medicine : public Card
{
public:
	enum class EMedicineType { MEDICINEJOKER, MEDICINEHEART, MEDICINESTOMACH, MEDICINEBRAIN, MEDICINEBONE};
	EMedicineType type;

	Medicine() {};
	Medicine(EMedicineType _type) : type(_type) {};

	void Draw()
	{
		switch (type)
		{
		case Medicine::EMedicineType::MEDICINEJOKER:
			ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::WHITE);
			std::cout << "Medicine - Joker | ";
			break;
		case Medicine::EMedicineType::MEDICINEHEART:
			ConsoleSetColor(ConsoleColor::RED, ConsoleColor::WHITE);
			std::cout << "Medicine - Heart | ";
			break;
		case Medicine::EMedicineType::MEDICINESTOMACH:
			ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::WHITE);
			std::cout << "Medicine - Stomach | ";
			break;
		case Medicine::EMedicineType::MEDICINEBRAIN:
			ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::WHITE);
			std::cout << "Medicine - Brain | ";
			break;
		case Medicine::EMedicineType::MEDICINEBONE:
			ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::WHITE);
			std::cout << "Medicine - Bone | ";
			break;
		default:
			break;
		}
	}
};

class Treatment : public Card
{
public:
	enum class ETreatmentType { INFECTION, ORGANTHIEF, TRASPLANT, LATEXGLOVE, MEDICALERROR};
	ETreatmentType type;

	Treatment() {};
	Treatment(ETreatmentType _type) : type(_type) {};

	void Draw()
	{
		switch (type)
		{
		case Treatment::ETreatmentType::INFECTION:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::WHITE);
			std::cout << "Treatment - Infection | ";
			break;
		case Treatment::ETreatmentType::ORGANTHIEF:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::WHITE);
			std::cout << "Treatment - Organ Thief | ";
			break;
		case Treatment::ETreatmentType::TRASPLANT:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::WHITE);
			std::cout << "Treatment - Trasplant | ";
			break;
		case Treatment::ETreatmentType::LATEXGLOVE:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::WHITE);
			std::cout << "Treatment - Latex glove | ";
			break;
		case Treatment::ETreatmentType::MEDICALERROR:
			ConsoleSetColor(ConsoleColor::CYAN, ConsoleColor::WHITE);
			std::cout << "Treatment - Medical error | ";
			break;
		default:
			break;
		}
	}
};
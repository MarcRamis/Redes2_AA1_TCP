#pragma once

#include <iostream>

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
			std::cout << "Organ - Joker | ";
			break;
		case Organ::EOrganType::HEART:
			std::cout << "Organ - Heart | ";
			break;
		case Organ::EOrganType::STOMACH:
			std::cout << "Organ - Stomach | ";
			break;
		case Organ::EOrganType::BRAIN:
			std::cout << "Organ - Brain | ";
			break;
		case Organ::EOrganType::BONE:
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
			std::cout << "Virus - Joker | ";
			break;
		case Virus::EVirusType::VIRUSHEART:
			std::cout << "Virus - Heart | ";
			break;
		case Virus::EVirusType::VIRUSSTOMACH:
			std::cout << "Virus - Stomach | ";
			break;
		case Virus::EVirusType::VIRUSBRAIN:
			std::cout << "Virus - Brain | ";
			break;
		case Virus::EVirusType::VIRUSBONE:
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
			std::cout << "Medicine - Joker | ";
			break;
		case Medicine::EMedicineType::MEDICINEHEART:
			std::cout << "Medicine - Heart | ";
			break;
		case Medicine::EMedicineType::MEDICINESTOMACH:
			std::cout << "Medicine - Stomach | ";
			break;
		case Medicine::EMedicineType::MEDICINEBRAIN:
			std::cout << "Medicine - Brain | ";
			break;
		case Medicine::EMedicineType::MEDICINEBONE:
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
			std::cout << "Treatment - Infection | ";
			break;
		case Treatment::ETreatmentType::ORGANTHIEF:
			std::cout << "Treatment - Organ Thief | ";
			break;
		case Treatment::ETreatmentType::TRASPLANT:
			std::cout << "Treatment - Trasplant | ";
			break;
		case Treatment::ETreatmentType::LATEXGLOVE:
			std::cout << "Treatment - Latex glove | ";
			break;
		case Treatment::ETreatmentType::MEDICALERROR:
			std::cout << "Treatment - Medical error | ";
			break;
		default:
			break;
		}
	}
};
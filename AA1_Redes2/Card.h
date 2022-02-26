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
			//std::cout << "joker\n";
			break;
		case Organ::EOrganType::HEART:
			//std::cout << "heart\n";
			break;
		case Organ::EOrganType::STOMACH:
			//std::cout << "stomach\n";
			break;
		case Organ::EOrganType::BRAIN:
			//std::cout << "brain\n";
			break;
		case Organ::EOrganType::BONE:
			//std::cout << "bone\n";
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

	Virus();
	Virus(EVirusType _type) : type(_type) {};
};

class Medicine : public Card
{
public:
	enum class EMedicineType { MEDICINEJOKER, MEDICINEHEART, MEDICINESTOMACH, MEDICINEBRAIN, MEDICINEBONE};
	EMedicineType type;

	Medicine() {};
	Medicine(EMedicineType _type) : type(_type) {};
};

class Treatment : public Card
{
public:
	enum class ETreatmentType { INFECTION, ORGANTHIEF, TRASPLANT, LATEXGLOVE, MEDICALERROR};
	ETreatmentType type;

	Treatment();
	Treatment(ETreatmentType _type) : type(_type) {};
};
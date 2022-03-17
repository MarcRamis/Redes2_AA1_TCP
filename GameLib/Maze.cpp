#include "Maze.h"

#include "Organ.h"
#include "Virus.h"
#include "Medicine.h"
#include "Treatment.h"


Maze::Maze()
{
	std::vector<Card*> tmpDeck;
	Card *card;
	// CREAR CARTAS DE ÓRGANOS
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			switch (i)
			{
			case 0:
				card = new Organ(Organ::EOrganType::HEART);
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Organ(Organ::EOrganType::STOMACH);
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Organ(Organ::EOrganType::BRAIN);
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Organ(Organ::EOrganType::BONE);
				tmpDeck.push_back(card);
				break;	
			}
		}
	}
	card = new Organ(Organ::EOrganType::JOKER);
	tmpDeck.push_back(card);

	// CREAR CARTAS DE VIRUS
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			switch (i)
			{
			case 0:
				card = new Virus(Virus::EVirusType::VIRUSHEART);
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Virus(Virus::EVirusType::VIRUSSTOMACH);
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Virus(Virus::EVirusType::VIRUSBRAIN);
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Virus(Virus::EVirusType::VIRUSBONE);
				tmpDeck.push_back(card);
				break;
			}
		}
	}
	card = new Virus(Virus::EVirusType::VIRUSJOKER);
	tmpDeck.push_back(card);

	// CREAR CARTAS DE MEDICINAS
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			switch (i)
			{
			case 0:
				card = new Medicine(Medicine::EMedicineType::MEDICINEHEART);
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Medicine(Medicine::EMedicineType::MEDICINESTOMACH);
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Medicine(Medicine::EMedicineType::MEDICINEBRAIN);
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Medicine(Medicine::EMedicineType::MEDICINEBONE);
				tmpDeck.push_back(card);
				break;
			case 4:
				card = new Medicine(Medicine::EMedicineType::MEDICINEJOKER);
				tmpDeck.push_back(card);
				break;
			}
		}
	}

	//CREAR CARTAS DE TRATAMIENTOS
	card = new Treatment(Treatment::ETreatmentType::INFECTION);
	tmpDeck.push_back(card);
	card = new Treatment(Treatment::ETreatmentType::INFECTION);
	tmpDeck.push_back(card);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (i)
			{
			case 0:
				card = new Treatment(Treatment::ETreatmentType::ORGANTHIEF);
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Treatment(Treatment::ETreatmentType::TRASPLANT);
				tmpDeck.push_back(card);
				break;
			}
		}
	}
	card = new Treatment(Treatment::ETreatmentType::LATEXGLOVE);
	tmpDeck.push_back(card);
	card = new Treatment(Treatment::ETreatmentType::MEDICALERROR);
	tmpDeck.push_back(card);

	// RANDOMIZAR LA BARAJA
	std::random_shuffle(tmpDeck.begin(), tmpDeck.end());

	// AÑADIRLA AL STACK DE CARTAS
	for(int i = 0; i < tmpDeck.size(); i++)
	{
		deck.push(tmpDeck[i]);
	}
}

std::vector<Card*> Maze::DealCards(unsigned int maxCardsToDeal)
{
	std::vector<Card*> tmpHand;

	for (int i = 0; i < maxCardsToDeal; i++)
	{
		tmpHand.push_back(deck.top());
		deck.pop();
	}
	return tmpHand;
}

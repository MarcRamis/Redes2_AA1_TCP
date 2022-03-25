#include "Maze.h"

#include "Organ.h"
#include "Virus.h"
#include "Medicine.h"
#include "Treatment.h"


Maze::Maze()
{
	std::vector<Card*> tmpDeck;
	Card *card;

	int counter = 0;
	// CREAR CARTAS DE ÓRGANOS
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			switch (i)
			{
			case 0:
				card = new Organ(Organ::EOrganType::HEART);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Organ(Organ::EOrganType::STOMACH);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Organ(Organ::EOrganType::BRAIN);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Organ(Organ::EOrganType::BONE);
				card->id = counter;
				tmpDeck.push_back(card);
				break;	
			}
			counter++;
		}
	}
	card = new Organ(Organ::EOrganType::JOKER);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;

	// CREAR CARTAS DE VIRUS
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			switch (i)
			{
			case 0:
				card = new Virus(Virus::EVirusType::VIRUSHEART);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Virus(Virus::EVirusType::VIRUSSTOMACH);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Virus(Virus::EVirusType::VIRUSBRAIN);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Virus(Virus::EVirusType::VIRUSBONE);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			}
			counter++;
		}
	}
	card = new Virus(Virus::EVirusType::VIRUSJOKER);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;

	// CREAR CARTAS DE MEDICINAS
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			switch (i)
			{
			case 0:
				card = new Medicine(Medicine::EMedicineType::MEDICINEHEART);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Medicine(Medicine::EMedicineType::MEDICINESTOMACH);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 2:
				card = new Medicine(Medicine::EMedicineType::MEDICINEBRAIN);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 3:
				card = new Medicine(Medicine::EMedicineType::MEDICINEBONE);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 4:
				card = new Medicine(Medicine::EMedicineType::MEDICINEJOKER);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			}
			counter++;
		}
	}

	//CREAR CARTAS DE TRATAMIENTOS
	card = new Treatment(Treatment::ETreatmentType::INFECTION);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;
	card = new Treatment(Treatment::ETreatmentType::INFECTION);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (i)
			{
			case 0:
				card = new Treatment(Treatment::ETreatmentType::ORGANTHIEF);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			case 1:
				card = new Treatment(Treatment::ETreatmentType::TRASPLANT);
				card->id = counter;
				tmpDeck.push_back(card);
				break;
			}
			counter++;
		}
	}
	card = new Treatment(Treatment::ETreatmentType::LATEXGLOVE);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;
	card = new Treatment(Treatment::ETreatmentType::MEDICALERROR);
	card->id = counter;
	tmpDeck.push_back(card);
	counter++;

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

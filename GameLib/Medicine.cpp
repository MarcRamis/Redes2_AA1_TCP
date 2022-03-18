#include "Medicine.h"

Medicine::Medicine()
{
}

Medicine::Medicine(EMedicineType _type) : type(_type) { cardType = EType::MEDICINE; }

void Medicine::Draw()
{
	switch (type)
	{
	case Medicine::EMedicineType::MEDICINEJOKER:
		ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::BLACK);
		std::cout << "Medicine - Joker | ";
		break;
	case Medicine::EMedicineType::MEDICINEHEART:
		ConsoleSetColor(ConsoleColor::RED, ConsoleColor::BLACK);
		std::cout << "Medicine - Heart | ";
		break;
	case Medicine::EMedicineType::MEDICINESTOMACH:
		ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::BLACK);
		std::cout << "Medicine - Stomach | ";
		break;
	case Medicine::EMedicineType::MEDICINEBRAIN:
		ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::BLACK);
		std::cout << "Medicine - Brain | ";
		break;
	case Medicine::EMedicineType::MEDICINEBONE:
		ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::BLACK);
		std::cout << "Medicine - Bone | ";
		break;
	default:
		break;
	}

	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}
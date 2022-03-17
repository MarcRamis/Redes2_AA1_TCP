#include "Organ.h"

Organ::Organ()
{
}

Organ::Organ(EOrganType _type) : type(_type) {};

void Organ::Draw()
{
	switch (type)
	{
	case Organ::EOrganType::JOKER:
		ConsoleSetColor(ConsoleColor::MAGENTA, ConsoleColor::BLACK);
		std::cout << "Organ - Joker | ";
		break;
	case Organ::EOrganType::HEART:
		ConsoleSetColor(ConsoleColor::RED, ConsoleColor::BLACK);
		std::cout << "Organ - Heart | ";
		break;
	case Organ::EOrganType::STOMACH:
		ConsoleSetColor(ConsoleColor::GREEN, ConsoleColor::BLACK);
		std::cout << "Organ - Stomach | ";
		break;
	case Organ::EOrganType::BRAIN:
		ConsoleSetColor(ConsoleColor::BLUE, ConsoleColor::BLACK);
		std::cout << "Organ - Brain | ";
		break;
	case Organ::EOrganType::BONE:
		ConsoleSetColor(ConsoleColor::DARKYELLOW, ConsoleColor::BLACK);
		std::cout << "Organ - Bone | ";
		break;
	default:
		break;
	}

	ConsoleSetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
}

void Organ::ImmunizeOrgan()
{ 
	std::cout << "Inmunizar" << std::endl; 
}

void Organ::InfectateOrgan()
{ 
	std::cout << "Infectar" << std::endl;
}

void Organ::VacunateOrgan()
{
	std::cout << "Vacunar" << std::endl; 
}
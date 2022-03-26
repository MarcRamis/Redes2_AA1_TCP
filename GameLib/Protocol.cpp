#include "Protocol.h"

void Protocol::Peer::AckPassword(TcpSocket* client, std::string& gameName)
{
	std::string txtPassword = " ";
	std::cout << "Write the correct password: " << std::endl;
	std::cin >> txtPassword;

	OutputMemoryStream pack;
	pack.Write(static_cast<int>(Protocol::PEER_BSSProtocol::ACK_PWD));
	pack.WriteString(gameName);
	pack.WriteString(txtPassword);
	Status status = client->Send(pack);
	if (status.GetStatus() != Status::EStatusType::DONE)
	{
		std::cout << "No se envio la password" << std::endl;
	}
}

void Protocol::Peer::Chat(std::vector<TcpSocket*>* _clientes, bool& isChat)
{
	std::string opc;

	while (opc != "exit")
	{
		if (isChat)
		{
			std::cout << "Write a message: " << std::endl;
			//std::getline(std::cin, opc);
			std::cin >> opc;

			OutputMemoryStream pack;
			pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::SENDMESSAGE));
			pack.WriteString(opc);

			for (size_t i = 0; i < _clientes->size(); i++)
			{
				Status status = (_clientes->at(i))->Send(pack);
				if (status.GetStatus() != Status::EStatusType::DONE)
				{
					std::cout << "El mensaje enviado Peer2Peer no se ha enviado: " << std::endl;
				}
			}
		}

	}
}

void Protocol::Peer::SendPlayOrgan(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed)
{
	OutputMemoryStream pack;
	for (int i = 0; i < _clientes->size(); i++)
	{
		pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::PLAYORGAN));

		pack.Write(idPlayerThatUsedCard); pack.Write(idCardPlayed); // id player that used a card & the position of his card

		Status status = _clientes->at(i)->Send(pack);
		if (status.GetStatus() != Status::EStatusType::DONE)
		{
			std::cout << "El mensaje Peer2Peer no se ha enviado: [ No se ha enviado la carta jugada ]" << std::endl;
		}
	}
}

void Protocol::Peer::ReceivedPlayedOrgan(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p)
{
	// Read all ids
	int idPlayerThatUsedCard = 0; int idCardPlayed = 0;
	pack.Read(&idPlayerThatUsedCard); pack.Read(&idCardPlayed);

	for (int i = 0; i < p.idOtherPlayers.size(); i++)
	{
		if (p.idOtherPlayers.at(i) == idPlayerThatUsedCard)
		{
			// Add the card played for other player & erase from his hand, also he needs to draw a new one 
			p.otherPlayedCards.at(i).push_back(p.otherhands.at(i).at(idCardPlayed));
			p.otherhands.at(i).erase(p.otherhands.at(i).begin() + idCardPlayed);
			std::vector<Card*> tmpCards = p.maze->DealCards(1);
			for (Card* c : tmpCards)
			{
				p.otherhands.at(i).push_back(c);
			}
			break;
		}
	}

}

void Protocol::Peer::SendInfectOrgan(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed, int idPlayerAffected, int idCardFromPlayerAffected)
{
	OutputMemoryStream pack;
	for (int i = 0; i < _clientes->size(); i++)
	{
		pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::INFECTORGAN));

		pack.Write(idPlayerThatUsedCard); pack.Write(idCardPlayed); // id player that used a card & the position of his card
		pack.Write(idPlayerAffected); pack.Write(idCardFromPlayerAffected); // id player that the card has affected & the id of his card

		Status status = _clientes->at(i)->Send(pack);
		if (status.GetStatus() != Status::EStatusType::DONE)
		{
			std::cout << "El mensaje Peer2Peer no se ha enviado: [ No se ha enviado la carta jugada ]" << std::endl;
		}
	}
}

void Protocol::Peer::ReceivedOrganInfected(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p)
{
	// Read all ids
	int idPlayerThatUsedCard = 0; int idCardPlayed = 0;
	int idPlayerAffected = 0; int idCardFromPlayerAffected = 0;
	pack.Read(&idPlayerThatUsedCard); pack.Read(&idCardPlayed); // receive player & card id used
	pack.Read(&idPlayerAffected); pack.Read(&idCardFromPlayerAffected); // receive player & card id who affect this card


	std::cout << "Player that used card: " << idPlayerThatUsedCard << std::endl;
	std::cout << "Player affected: " << idPlayerAffected << std::endl;
	std::cout << "Card used: " << idCardPlayed << std::endl;
	std::cout << "Card affected: " << idCardFromPlayerAffected << std::endl << std::endl;

	std::cout << "My id: " << p.id << std::endl;

	// search if the player is me
	int id_card = p.FindPositionCardbyIDCardInPlayedCards(idCardFromPlayerAffected);
	std::cout << "Posicion de la carta en contenedor: " << id_card << std::endl;;
	
	if (id_card != -1)
	{
		std::cout << "soy yo entra" << std::endl;
		if (p.hand.at(id_card)->state == Card::EOrganState::INFECTED) {
			p.maze->discardDeck.push(p.hand.at(id_card)); // This add the card to the discard deck
			p.hand.erase(p.hand.begin() + id_card); // This deletes the card from the table
		}
		else
		{
			std::cout << "infecta la carta" << std::endl;
			p.hand.at(id_card)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
		}
		
		// discard the card used
		for (int i = 0; i < p.idOtherPlayers.size(); i++)
		{
			if (p.idOtherPlayers.at(i) == idPlayerThatUsedCard)
			{
				std::cout << "se descarta la carta jugada" << std::endl;
				// Discard card used
				// Add the card played for other player & erase from his hand, also he needs to draw a new one
				p.maze->discardDeck.push(p.otherhands.at(i).at(idCardPlayed));
				p.otherhands.at(i).erase(p.otherhands.at(i).begin() + idCardPlayed);
				std::vector<Card*> tmpCards = p.maze->DealCards(1);
				for (Card* c : tmpCards)
				{
					p.otherhands.at(i).push_back(c);
				}
				break;
			}
		}
	}
	else
	{

	}



	//if (p.id == idPlayerAffected)
	//{
	//	playerIsMe = true;
	//	// Infect
	//	// If it was infected before, then dies
	//
	//	if (p.hand.at(id_card)->state == Card::EOrganState::INFECTED) {
	//		p.maze->discardDeck.push(p.hand.at(id_card)); // This add the card to the discard deck
	//		p.hand.erase(p.hand.begin() + id_card); // This deletes the card from the table
	//	}
	//	else
	//	{
	//		std::cout << "a" << std::endl;
	//		p.hand.at(id_card)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
	//	}
	//	
	//	// discard the card used
	//	for (int i = 0; i < p.idOtherPlayers.size(); i++)
	//	{
	//		if (p.idOtherPlayers.at(i) == idPlayerThatUsedCard)
	//		{
	//			std::cout << "se descarta la carta jugada" << std::endl;
	//			// Discard card used
	//			// Add the card played for other player & erase from his hand, also he needs to draw a new one
	//			p.maze->discardDeck.push(p.otherhands.at(i).at(idCardPlayed));
	//			p.otherhands.at(i).erase(p.otherhands.at(i).begin() + idCardPlayed);
	//			std::vector<Card*> tmpCards = p.maze->DealCards(1);
	//			for (Card* c : tmpCards)
	//			{
	//				p.otherhands.at(i).push_back(c);
	//			}
	//			break;
	//		}
	//	}
	//}
	//
	//// Look if the card to affect is not mine
	//if (!playerIsMe)
	//{
	//	std::cout << "Player is not me" << std::endl;
	//	for (int i = 0; i < p.otherPlayedCards.size(); i++)
	//	{
	//		// Infect 
	//		for (int j = 0; j < p.otherPlayedCards.at(i).size(); j++)
	//		{
	//			std::cout << "entra" << std::endl;
	//			// If it was infected before, then dies
	//			if (p.otherPlayedCards.at(j).at(idCardFromPlayerAffected)->state == Card::EOrganState::INFECTED) {
	//				std::cout << "entra2 if" << std::endl;
	//				p.maze->discardDeck.push(p.otherPlayedCards.at(i).at(idCardFromPlayerAffected)); // This add the card to the discard deck
	//				p.otherPlayedCards.at(j).erase(p.otherPlayedCards.at(i).begin() + idCardFromPlayerAffected); // This deletes the card from the table
	//			}
	//			else
	//			{
	//				std::cout << "entra2 else" << std::endl;
	//				p.otherPlayedCards.at(j).at(idCardFromPlayerAffected)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
	//			}
	//			break;
	//		}
	//	}
	//	
	//	for (int i = 0; i < p.idOtherPlayers.size(); i++)
	//	{
	//		if (p.idOtherPlayers.at(i) == idPlayerThatUsedCard)
	//		{
	//			// Discard card used
	//			// Add the card played for other player & erase from his hand, also he needs to draw a new one
	//			p.maze->discardDeck.push(p.otherhands.at(i).at(idCardPlayed));
	//			p.otherhands.at(i).erase(p.otherhands.at(i).begin() + idCardPlayed);
	//			std::vector<Card*> tmpCards = p.maze->DealCards(1);
	//			for (Card* c : tmpCards)
	//			{
	//				p.otherhands.at(i).push_back(c);
	//			}
	//			break;
	//		}
	//	}
	//}
}

void Protocol::Peer::SendDiscardCard(std::vector<TcpSocket*>* _clientes, int idPlayerThatDiscard, int numberCards)
{
	OutputMemoryStream pack;
	pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::DISCARDCARDS));

	pack.Write(idPlayerThatDiscard); pack.Write(numberCards); // id player that discard & the number of cards

	for (int i = 0; i < _clientes->size(); i++)
	{
		Status status = _clientes->at(i)->Send(pack);
		if (status.GetStatus() != Status::EStatusType::DONE)
		{
			std::cout << "El mensaje Peer2Peer no se ha enviado: [ No se ha enviado la carta jugada ]" << std::endl;
		}
	}
}

void Protocol::Peer::ReceivedDiscardCard(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p)
{
	// Read all ids
	int idPlayerThatDiscard = 0; int numberOfCards = 0;
	pack.Read(&idPlayerThatDiscard); pack.Read(&numberOfCards);

	for (int i = 0; i < p.idOtherPlayers.size(); i++)
	{
		if (p.idOtherPlayers.at(i) == idPlayerThatDiscard)
		{

			for (int j = 0; j < numberOfCards; j++)
			{
				p.maze->discardDeck.push(p.otherhands.at(i).at(j));
			}
			for (int j = 0; j < numberOfCards; j++)
			{
				p.otherhands.at(i).erase(p.otherhands.at(i).begin());
			}
			std::vector<Card*> tmpCards = p.maze->DealCards(numberOfCards);
			for (Card* c : tmpCards)
			{
				p.otherhands.at(i).push_back(c);
			}

		}
	}
}

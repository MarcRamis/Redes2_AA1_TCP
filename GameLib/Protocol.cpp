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

	if (p.id == idPlayerAffected)
	{
		// If it was infected before, then dies
		if (p.hand.at(idCardFromPlayerAffected)->state == Card::EOrganState::INFECTED) {
			p.maze->discardDeck.push(p.hand.at(idCardFromPlayerAffected)); // This add the card to the discard deck
			p.hand.erase(p.hand.begin() + idCardFromPlayerAffected); // This deletes the card from the table
		}
		else
		{
			p.hand.at(idCardFromPlayerAffected)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
		}
	}

	// First look if the card to affect is not mine
	for (int i = 0; i < p.idOtherPlayers.size(); i++)
	{
		if (p.idOtherPlayers.at(i) == idPlayerThatUsedCard)
		{
			// Infect 
			for (int j = 0; j < p.otherPlayedCards.at(i).size(); j++)
			{
				std::cout << "entra" << std::endl;
				// If it was infected before, then dies
				if (p.otherPlayedCards.at(j).at(idCardFromPlayerAffected)->state == Card::EOrganState::INFECTED) {
					std::cout << "entra2 if" << std::endl;
					p.maze->discardDeck.push(p.otherPlayedCards.at(i).at(idCardFromPlayerAffected)); // This add the card to the discard deck
					p.otherPlayedCards.at(j).erase(p.otherPlayedCards.at(i).begin() + idCardFromPlayerAffected); // This deletes the card from the table
				}
				else
				{
					std::cout << "entra2 else" << std::endl;
					p.otherPlayedCards.at(j).at(idCardFromPlayerAffected)->state = Card::EOrganState::INFECTED; // here i'm just infecting the card
				}
				break;
			}
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
	std::cout << "se va";
}

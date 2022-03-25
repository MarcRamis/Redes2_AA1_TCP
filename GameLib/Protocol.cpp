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

	std::cout << "player id: " << idPlayerThatUsedCard << std::endl;
	std::cout << "card id: " << idCardPlayed << std::endl;

	for (int i = 0; i < p.otherhands.size(); i++)
	{
		std::cout << "id hand: " << i << " has" << std::endl;
		for (int j = 0; j < p.otherhands.at(i).size(); j++)
		{
			p.otherhands.at(i).at(j)->Draw();
		}
	}

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
		}
	}

}
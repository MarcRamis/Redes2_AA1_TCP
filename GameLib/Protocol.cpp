#include "Protocol.h"

void Protocol::Peer::AckPassword(TcpSocket* client, std::string &gameName)
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

void Protocol::Peer::Chat(std::vector<TcpSocket*>* _clientes, bool &isChat)
{
	std::string opc;

	while (opc != "exit")
	{
		if (isChat)
		{
			std::cout << "Write a message: " << std::endl;
			std::getline(std::cin, opc);

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

//void Protocol::Peer::PlayCard(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed, int idPlayerThatFirstPlayerAffected, int idCardAffected)
//{
//	//OutputMemoryStream pack;
//	//for (int i = 0; i < _clientes->size(); i++)
//	//{
//	//	pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::PLAYCARD));
//	//	
//	//	pack.Write(idPlayerThatUsedCard); pack.Write(idCardPlayed); // id player that used a card & the position of his card
//	//	pack.Write(idPlayerThatFirstPlayerAffected); pack.Write(idCardAffected); // id player the card used affected him & the position of his card
//	//	
//	//	Status status = _clientes->at(i)->Send(pack);
//	//	if (status.GetStatus() != Status::EStatusType::DONE)
//	//	{
//	//		std::cout << "El mensaje Peer2Peer no se ha enviado: [ No se ha enviado la carta jugada ]" << std::endl;
//	//	}
//	//}
//}
//
//void Protocol::Peer::ReceivedPlayedCard(InputMemoryStream pack, Player &p)
//{
//	// Read all ids
//	//int idPlayerThatUsedCard = 0, int idCardPlayed = 0, int idPlayerThatFirstPlayerAffected = 0, int idCardAffected = 0;
//	//pack.Read(&idPlayerThatUsedCard);
//	//pack.Read(&idCardPlayed);
//	//pack.Read(&idPlayerThatFirstPlayerAffected);
//	//pack.Read(&idCardAffected);
//	
//	// See if the card affected is mine or not
//	//if (*idPlayerThatFirstPlayerAffected == p.id)
//	//{
//	//	// Make the move
//	//	p.otherhands.at(*idPlayerThatUsedCard).at(*idCardPlayed)->Play(p, p.playedCards.at(*idCardAffected), *idCardPlayed);
//	//}
//	//else
//	//{
//	//	p.otherhands.at(*idPlayerThatUsedCard).at(*idCardPlayed)->Play(p, p.otherPlayedCards.at(*idPlayerThatFirstPlayerAffected).at(*idCardAffected), *idCardPlayed);
//	//}
//
//	
//}

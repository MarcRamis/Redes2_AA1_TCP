#include "Protocol.h"

void Protocol::AckPassword(TcpSocket* client, std::string gameName)
{
	std::string txtPassword = " ";
	std::cout << "Write the correct password: " << std::endl;
	std::cin >> txtPassword;

	OutputMemoryStream pack;
	pack.Write(static_cast<int>(Protocol::PEER_BSSProtocol::ACK_PWD));
	pack.WriteString(gameName);
	pack.WriteString(txtPassword);
	Status status = client->Send(pack);
}

void Protocol::Chat(std::vector<TcpSocket*>* _clientes, bool &isChat)
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

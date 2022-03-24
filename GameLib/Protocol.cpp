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

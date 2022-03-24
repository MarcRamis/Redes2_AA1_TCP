#pragma once

#include "Selector.h"
#include <string>

class Protocol
{
public:

	enum class PEER_BSSProtocol
	{
		CREATEMATCH, CONSULTMATCHLIST, JOINMATCH, ACK_PWD, NONE
	};
	enum class BSS_PEERProtocol
	{
		CREATEMATCH, MATCHLIST, ERROR, PEERMESSAGE, PEERPLAYERLIST, REQ_PWD, EXITBSSCOM, NONE
	};
	
	enum class PEER_PEERProtocol
	{
		SENDMESSAGE, ACKREADYFORGAME, ISREADY, NONE
	};

	static void AckPassword(TcpSocket* client, std::string gameName);
};
#pragma once

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
};
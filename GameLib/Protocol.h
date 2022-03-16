#pragma once

class Protocol
{
public:

	enum class PEER_BSSProtocol
	{
		CREATEMATCH, CONSULTMATCHLIST, JOINMATCH, NONE
	};
	enum class BSS_PEERProtocol
	{
		CREATEMATCH, MATCHLIST, ERROR, PEERMESSAGE, PEERPLAYERLIST, EXITBSSCOM, NONE
	};

	enum class PEER_PEERProtocol
	{
		SENDMESSAGE, NONE
	};

};
#pragma once

#include "Selector.h"
#include "Player.h"
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
		SENDMESSAGE, ACKREADYFORGAME, ISREADY, PLAYORGAN, NONE
	};

	static struct Peer
	{
		// Match protocols
		static void AckPassword(TcpSocket* client, std::string &gameName);
		static void Chat(std::vector<TcpSocket*>* _clientes, bool& isChat);
		
		// Card protocols
		static void SendPlayOrgan(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed);
		static void ReceivedPlayedOrgan(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p);
	};
	static struct Server
	{

	};
};
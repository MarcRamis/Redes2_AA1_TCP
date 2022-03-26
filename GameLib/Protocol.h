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
		MATCHLIST, ERROR, PEERPLAYERLIST, REQ_PWD, EXITBSSCOM, NONE
	};
	
	enum class PEER_PEERProtocol
	{
		SENDMESSAGE, ACKREADYFORGAME, ISREADY, PLAYORGAN, INFECTORGAN, VACUNATEORGAN, DISCARDCARDS, YOULOST, NONE
	};

	static struct Peer
	{
		// Match creation protocols
		static void AckPassword(TcpSocket* client, std::string &gameName);
		static void Chat(std::vector<TcpSocket*>* _clientes, bool& isChat);
		
		// Game protocols
		static void SendPlayOrgan(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed);
		static void ReceivedPlayedOrgan(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p);
		static void SendInfectOrgan(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed, int idCardFromPlayerAffected);
		static void ReceivedOrganInfected(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p);
		static void SendMedicineCard(std::vector<TcpSocket*>* _clientes, int idPlayerThatUsedCard, int idCardPlayed, int idCardFromPlayerAffected);
		static void ReceivedMedicineCard(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p);
		static void SendDiscardCard(std::vector<TcpSocket*>* _clientes, int idPlayerThatDiscard, int numberCards);
		static void ReceivedDiscardCard(std::vector<TcpSocket*>* _clientes, InputMemoryStream pack, Player& p);
		static void YouLost(std::vector<TcpSocket*>* _clientes);
	};
	static struct Server
	{

	};
};
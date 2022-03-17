#include <iostream>

#include "Selector.h"
#include "Match.h"
#include "Protocol.h"
#include "Constants.h"

#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>

std::mutex mtxConexiones;
int currentMatchKeys;

void JoinGame(Match tempGame, std::map<int, Match>* games, TcpSocket* client, std::vector <TcpSocket*>* _clientes, Selector selector, int it)
{
	OutputMemoryStream sendPacket;
	Port tmpPort;
	bool foundGame = false;

	for (size_t i = 0; i < games->size(); i++)
	{
		if (games->at(i).name == tempGame.name)
		{
			sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::PEERPLAYERLIST));
			sendPacket.Write(static_cast<int>(games->at(i).ports.size()));
			sendPacket.Write(static_cast<int>(games->at(i).maxPlayers));

			for (size_t j = 0; j < games->at(i).ports.size(); j++)
			{
				sendPacket.WriteString(games->at(i).ports.at(j).ip);
				sendPacket.Write(games->at(i).ports.at(j).port);
			}

			tmpPort.ip = client->GetRemoteIP();
			tmpPort.port = client->GetRemotePort().port;
			games->at(i).ports.push_back(tmpPort);
			foundGame = true;

			sendPacket.Write(static_cast<int>(games->at(i).ports.size()));
			client->Send(sendPacket);

			if (games->at(i).ports.size() >= games->at(i).maxPlayers)  //Comrpueba si la sala esta llena
			{
				games->erase(games->find(i));
			}
			break;
		}
		if (!foundGame)
		{
			std::string errorTxt = "Game could't be found";

			sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::ERROR));
			sendPacket.WriteString(errorTxt);
			client->Send(sendPacket);
		}
		else
		{
			_clientes->erase(_clientes->begin() + it);
			selector.Remove(client);
			client->Disconnect();
			delete client;
			it--;
		}
	}
}

void ControlServidor(std::vector<TcpSocket*>* _clientes, std::map<int,Match>* games)
{
	bool running = true;

	TcpListener listener;
	Status status = listener.Listen(PORT);
	if (status.GetStatus() != Status::EStatusType::DONE)
	{
		std::cout << "Error al abrir listener\n";
		exit(0);
	}

	Selector selector;
	selector.Add(&listener);
	
	while (true)
	{
		std::cout << "Waiting connection" << std::endl;
		if (selector.Wait())
		{
			if (selector.IsReady(&listener))
			{
				TcpSocket* client = new TcpSocket;
				if (listener.Accept(client).GetStatus() == Status::EStatusType::DONE)
				{
					std::cout << "Llega el cliente con puerto: " << client->GetRemotePort().port << std::endl;
					_clientes->push_back(client);
					selector.Add(client);
				}
				else
				{
					std::cout << "Error al recoger conexión nueva\n";
					delete client;
				}
			}
			else
			{
				mtxConexiones.lock();
				for (size_t it = 0; it < _clientes->size(); ++it)
				{
					TcpSocket* client = _clientes->at(it);
					if (selector.IsReady(client))
					{
						// The client has sent some data, we can receive it
						InputMemoryStream packet = *client->Receive();
						if (client->StatusReceived().GetStatus() == Status::EStatusType::DONE)
						{
							std::cout << "Recibido mensaje de Peer" << std::endl;

							int type;
							packet.Read(&type);
							
							Match tempGame;
							Port tmpPort;

							bool nameRepeats = false;
							bool foundGame = false;
							
							OutputMemoryStream sendPacket;
							switch (static_cast<Protocol::PEER_BSSProtocol>(type))
							{
							case Protocol::PEER_BSSProtocol::CREATEMATCH:
								
								std::cout << "Creando juego" << std::endl;

								tempGame.name = packet.ReadString(); // Save game name
								
								for (size_t i = 0; i < games->size(); i++)
								{
									if (games->at(i).name == tempGame.name)
									{
										std::string textError = "Game name exists";
										sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::ERROR));
										sendPacket.WriteString(textError);
										client->Send(sendPacket);
										nameRepeats = true;
										
										break;
									}
								}
								if (!nameRepeats)
								{
									// SET PARAMETERS 
									packet.Read(&tempGame.maxPlayers);
									tmpPort.ip = client->GetRemoteIP();
									tmpPort.port = client->GetRemotePort().port;
									tempGame.ports.push_back(tmpPort);
									
									packet.Read(&tempGame.hasPassword);
									if (tempGame.hasPassword)
									{
										tempGame.pw = packet.ReadString();
									}
									
									std::string textDebug = "The game was created";
									std::cout << textDebug << std::endl;
									games->insert(std::pair<int,Match>(currentMatchKeys, tempGame));
									currentMatchKeys++;

									sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::EXITBSSCOM));
									sendPacket.WriteString(textDebug);
									client->Send(sendPacket);
									
									//Cerrar comunicacion con este socket
									_clientes->erase(_clientes->begin() + it);
									selector.Remove(client);
									client->Disconnect();
									delete client;
									it--;
								}

								break;
								
							case Protocol::PEER_BSSProtocol::CONSULTMATCHLIST:
								
								sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::MATCHLIST));
								sendPacket.Write(static_cast<int>(games->size()));
								for (size_t i = 0; i < games->size(); i++)
								{
									sendPacket.WriteString(games->at(i).name);
									sendPacket.Write(games->at(i).maxPlayers);
									sendPacket.Write(static_cast<int>(games->at(i).ports.size()));
									sendPacket.Write(games->at(i).hasPassword);
								}
								client->Send(sendPacket);
								break;

							case Protocol::PEER_BSSProtocol::ACKPASSWORD:
								
								tempGame.name = packet.ReadString();
								for (size_t i = 0; i < games->size(); i++)
								{
									if (games->at(i).name == tempGame.name)
									{
										// To make the current client to join match know if there is password										
										if (games->at(i).hasPassword)
										{
											sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::WRITEPASSWORD));
											sendPacket.WriteString(games->at(i).pw);
											client->Send(sendPacket);
										}
										else
										{
											sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::NOPASSWORD));
											client->Send(sendPacket);
										}
										break;
									}
								}
								break;
							case Protocol::PEER_BSSProtocol::JOINMATCH:
								
								tempGame.name = packet.ReadString();
								JoinGame(tempGame, games, client, _clientes,selector, it);

								break;
								
							case Protocol::PEER_BSSProtocol::NONE:
								std::cout << "Error de tipo de mensaje por NONE" << std::endl;
								break;
							default:
								std::cout << "Error de tipo de mensaje no lo pudo identificar" << std::endl;
								break;
							}

						}
						else if (client->StatusReceived().GetStatus() == Status::EStatusType::DISCONNECTED)
						{
							_clientes->erase(_clientes->begin() + it);
							selector.Remove(client);
							client->Disconnect();
							delete client;
							it--;

							std::cout << "Elimino el socket que se ha desconectado\n";
						}
						else
						{
							std::cout << "Error al recibir de " << client->GetRemotePort().port << std::endl;
						}
					}
				}
				mtxConexiones.unlock();
			}
		}

	}

	listener.Disconnect();
}

int main()
{
	std::vector<Port*> ids;
	std::vector<TcpSocket*> clientes;
	std::map<int, Match> games;
	
	ControlServidor(&clientes, &games);

	return 0;
}
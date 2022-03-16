#include <iostream>

#include "Selector.h"
#include "Match.h"
#include "Protocol.h"

#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>

std::mutex mtxConexiones;
int currentMatchKeys;


void ControlServidor(std::vector<TcpSocket*>* _clientes, std::map<int,Match>* games)
{
	bool running = true;

	TcpListener listener;
	Status status = listener.Listen(50000);
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
					std::cout << "Error al recoger conexi�n nueva\n";
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

							std::string strRec;
							int type;
							packet.Read(&type);
							
							Match tempGame;
							Port tempPort;

							bool nameRepeats = false;
							bool foundGame = false;
							bool thereIsPassword = false;
							
							OutputMemoryStream sendPacket;

							switch (static_cast<Protocol::PEER_BSSProtocol>(type))
							{
							case Protocol::PEER_BSSProtocol::CREATEMATCH:
								
								std::cout << "Creando juego" << std::endl;

								tempGame.name = packet.ReadString(); // GUARDO NOMBRE DE LA PARTIDA 
								
								for (size_t i = 0; i < games->size(); i++) // MIRAMOS QUE SEA LA PARTIDA INDICADA 
								{
									if (games->at(i).name == tempGame.name)
									{
										std::string textError = "El nombre ya existe";
										sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::ERROR));
										sendPacket.WriteString(textError);
										client->Send(sendPacket);
										nameRepeats = true;
										
										break;
									}
								}
								if (!nameRepeats) // Y QUE NO SE REPTIA EL NOMBRE DE LA PARTIDA
								{
									// SET PARAMETERS 
									packet.Read(&tempGame.maxPlayers);
									tempPort.ip = client->GetRemoteIP();
									tempPort.port = client->GetRemotePort().port;
									tempGame.currentPlayers.push_back(tempPort);
									
									packet.Read(&thereIsPassword);
									
									if (thereIsPassword)
									{
										tempGame.pw = packet.ReadString();
									}
									
									std::cout << "Partida creada" << std::endl;
									games->insert(std::pair<int,Match>(currentMatchKeys,tempGame));
									currentMatchKeys++;

									std::string textError = "Servidor creado";
									sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::EXITBSSCOM));
									sendPacket.WriteString(textError);
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
									sendPacket.Write(static_cast<int>(games->at(i).currentPlayers.size()));
									sendPacket.Write(thereIsPassword);
								}
								client->Send(sendPacket);
								break;

							case Protocol::PEER_BSSProtocol::JOINMATCH:
								
								strRec = packet.ReadString();

								for (size_t i = 0; i < games->size(); i++)
								{
									if (games->at(i).name == strRec)
									{
										sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::PEERPLAYERLIST));
										sendPacket.Write(static_cast<int>(games->at(i).currentPlayers.size()));
										for (size_t j = 0; j < games->at(i).currentPlayers.size(); j++)
										{ 
											sendPacket.WriteString(games->at(i).currentPlayers.at(j).ip);
											sendPacket.Write(games->at(i).currentPlayers.at(j).port);
										}
										client->Send(sendPacket);
										
										tempPort.ip = client->GetRemoteIP();
										tempPort.port = client->GetRemotePort().port;
										games->at(i).currentPlayers.push_back(tempPort);
										foundGame = true;
										if (games->at(i).currentPlayers.size() >= games->at(i).maxPlayers)  //Comrpueba si la sala esta llena
										{
											games->erase(games->find(i));
										}
										break;
									}
								}

								if (foundGame)
								{
									_clientes->erase(_clientes->begin() + it);
									selector.Remove(client);
									client->Disconnect();
									delete client;
									it--;
								}
								else
								{
									std::string errorTxt = "Game could't be found";

									sendPacket.Write(static_cast<int>(Protocol::BSS_PEERProtocol::ERROR));
									sendPacket.WriteString(errorTxt);
									client->Send(sendPacket);
								}

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
	std::map<int,Match> games;
	
	ControlServidor(&clientes, &games);

	return 0;
}
#include <iostream>

#include <Selector.h>
#include "Protocol.h"

#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>

std::mutex mtxConexiones;
unsigned int _localPort;


void ControlServidor(std::vector<TcpSocket*>* _clientes, Selector* _selector, TcpSocket* _socketBSS, bool* _exitBSS, bool * _continueBSS)
{
	bool running = true;

	// Endless loop that waits for new connections
	while (!(*_exitBSS))
	{
		// Make the selector wait for data on any socket
		InputMemoryStream packet = *_socketBSS->Receive();
		Status status = _socketBSS->StatusReceived();

		if (status.GetStatus() == Status::EStatusType::DONE)
		{
			std::string strRec;
			int tempInt;

			//Games List variables
			int sizeGamesList;
			std::string serverName;
			int maxPlayers;
			int currentPlayers;
			bool hasPassWord;

			//Join Game variables
			int sizeGamesPlayers;
			Port port;
			bool anErrorWithConnection = false;

			packet.Read(&tempInt);

			if (!(*_exitBSS))
			{
				switch (static_cast<Protocol::BSS_PEERProtocol>(tempInt))
				{
				case Protocol::BSS_PEERProtocol::MATCHLIST:

					packet.Read(&sizeGamesList);

					for (int i = 0; i < sizeGamesList; i++)
					{
						serverName = packet.ReadString();
						packet.Read(&maxPlayers);
						packet.Read(&currentPlayers);
						packet.Read(&hasPassWord);
						
						std::cout << "Nombre de la partida: " << serverName << " Jugadores: " << currentPlayers << " / " << maxPlayers << " Tiene contraseña: ";
						if (hasPassWord) 
							std::cout << "Yes" << std::endl;
						else
							std::cout << "No" << std::endl;
					}

					*_continueBSS = false;
					break;

				case Protocol::BSS_PEERProtocol::ERROR:

					strRec = packet.ReadString(); // recibo mensaje de errror
					std::cout << strRec << std::endl;
					*_continueBSS = false;

					break;

				case Protocol::BSS_PEERProtocol::PEERMESSAGE:
					break;

				case Protocol::BSS_PEERProtocol::PEERPLAYERLIST:

					packet.Read(&sizeGamesPlayers);

					for (int i = 0; i < sizeGamesPlayers; i++)
					{
						port.ip = packet.ReadString();
						packet.Read(&port.port);

						TcpSocket* tempSock = new TcpSocket();
						status = tempSock->Connect(port.ip, port.port);

						switch (status.GetStatus())
						{
						case Status::EStatusType::DONE:
							
							_clientes->push_back(tempSock);
							_selector->Add(tempSock);
							std::cout << "Se pudo conectar a " << port.ip << " con puerto " << port.port << std::endl;
							
							break;
							
						case Status::EStatusType::DISCONNECTED:
							std::cout << "Se desconecto de " << port.ip << " con puerto " << port.port << std::endl;
							break;
							
						default:
							std::cout << "No se pudo conectar a " << port.ip << " con puerto " << port.port << std::endl;
							anErrorWithConnection = true;
							break;
						}

					}

					if (anErrorWithConnection)
					{
						// Reiniciar sockets y listeners
						*_continueBSS = false;
					}
					else
					{
						_socketBSS->Disconnect();
						delete _socketBSS;
						*_exitBSS = true;
					}

					break;
				case Protocol::BSS_PEERProtocol::EXITBSSCOM:

					strRec = packet.ReadString();
					std::cout << strRec << std::endl;
					*_exitBSS = true;
					std::cout << strRec << std::endl;
					_socketBSS->Disconnect();
					delete _socketBSS;
					
					break;
				
				case Protocol::BSS_PEERProtocol::NONE:
					break;
				default:
					break;
				}
			}
		}
		else if (status.GetStatus() == Status::EStatusType::DISCONNECTED)
		{
			_socketBSS->Disconnect();
			delete _socketBSS;
			std::cout << "Elimino el socket que se ha desconectado BSS\n";
		}
		else
		{
			std::cout << "Error al recibir de BSS" << std::endl;
		}
	}
}

void ControlPeers(std::vector<TcpSocket*>* _clientes, Selector* _selector, TcpListener* _listener, bool* _exitBSS, bool* _continueBSS)
{
	bool running = true;

	// Create a socket to listen to new connections
	Status status = _listener->Listen(_localPort);
	if (status.GetStatus() != Status::EStatusType::DONE)
	{
		std::cout << "Error al abrir listener\n";
		exit(0);
	}
	
	_selector->Add(_listener);

	// Endless loop that waits for new connections
	while (running)
	{
		// Make the selector wait for data on any socket
		if (_selector->Wait())
		{
			//std::cout << "Entro BBSS" << std::endl;
			// Test the listener
			if (_selector->IsReady(_listener))
			{
				// The listener is ready: there is a pending connection
				TcpSocket* client = new TcpSocket;
				if (_listener->Accept(client).GetStatus() == Status::EStatusType::DONE)
				{
					mtxConexiones.lock();

					// Add the new client to the clients list
					std::cout << "Llega el cliente con puerto: " << client->GetRemotePort().port << std::endl;
					_clientes->push_back(client);
					// Add the new client to the selector so that we will
					// be notified when he sends something
					_selector->Add(client);
					
					if (_clientes->size() == 4) 
						_selector->Remove(_listener);

					mtxConexiones.unlock();
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					std::cout << "Error al recoger conexión nueva\n";
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				mtxConexiones.lock();
				for (int it = 0; it < _clientes->size(); ++it)
				{
					TcpSocket* client = _clientes->at(it);
					if (_selector->IsReady(client))
					{
						// The client has sent some data, we can receive it
						InputMemoryStream packet = *client->Receive();

						if (status.GetStatus() == Status::EStatusType::DONE)
						{
							std::string strRec;
							int tempInt;

							packet.Read(&tempInt);

							switch (static_cast<Protocol::PEER_PEERProtocol>(tempInt))
							{
							case Protocol::PEER_PEERProtocol::SENDMESSAGE:

								strRec = packet.ReadString();
								std::cout << "He recibido un mensaje: " << strRec << " del puerto " << client->GetRemotePort().port << std::endl;
								break;

							case Protocol::PEER_PEERProtocol::NONE:
								std::cout << "Error de None" << std::endl;
								break;

							default:
								std::cout << "Error de no encontrar tipo enum" << std::endl;
								break;
							}

						}
						else if (status.GetStatus() == Status::EStatusType::DISCONNECTED)
						{
							_clientes->erase(_clientes->begin() + it);
							_selector->Remove(client);
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
}

void ConnectToBSS(std::vector<TcpSocket*>* _clientes, Selector* _selector, bool* _exitBSS, bool* _continueBSS)
{
	TcpSocket* sock = new TcpSocket();
	sock->Connect("localhost", 50000);

	_localPort = sock->GetLocalPort().port;
	// std::cout << "Port: " << _localPort << std::endl;

	std::thread messagesServer(ControlServidor, _clientes, _selector, sock, _exitBSS, _continueBSS);
	messagesServer.detach();

	// Parameters to write
	std::string opc;
	int numPlayers;
	bool hasPassword = false;

	do
	{
		if ((*_continueBSS))
		{
			continue;
		}
		std::cout << "1 - Crear una partida " << std::endl 
			<< "2 - Ver lista de partidas" << std::endl 
			<< "3 - Unirte a una partida" << std::endl;

		std::cin >> opc;
		
		OutputMemoryStream pack;

		if (opc == "1")
		{
			pack.Write(static_cast<int>(Protocol::PEER_BSSProtocol::CREATEMATCH));

			std::cout << "Escribe el nombre de la partida: " << std::endl;
			std::cin >> opc;
			pack.WriteString(opc);
			
			std::cout << "Escribe el numero de jugadores: " << std::endl;
			std::cin >> numPlayers;
			pack.Write(numPlayers);
			
			std::cout << "Servidor con password: 1-Si 2-No " << std::endl;
			std::cin >> numPlayers;
			if (numPlayers == 1)
			{
				hasPassword = true;
				pack.Write(hasPassword);

				std::cout << "Escribe la password: " << std::endl;
				std::cin >> opc;
				pack.WriteString(opc);
			}
			else
			{
				hasPassword = false;
				pack.Write(hasPassword);
			}

			pack.Write(_localPort);

			Status status = sock->Send(pack);
			if (status.GetStatus() != Status::EStatusType::DONE)
			{
				std::cout << "//////////////////// No se ha podido enviar el mensaje con la informacion para crear partida ////////////////////" << std::endl;
			}
		}
		else if (opc == "2")
		{
			pack.Write(static_cast<int>(Protocol::PEER_BSSProtocol::CONSULTMATCHLIST));
			Status status = sock->Send(pack);

			if (status.GetStatus() != Status::EStatusType::DONE)
			{
				std::cout << "//////////////////// No se ha podido enviar el mensaje con la informacion para ver las partidas ////////////////////" << std::endl;
			}
		}
		else if (opc == "3")
		{
			pack.Write(static_cast<int>(Protocol::PEER_BSSProtocol::JOINMATCH));
			
			std::cout << "Escribe el nombre de la partida: " << std::endl;
			std::cin >> opc;
			pack.WriteString(opc);
			

			Status status = sock->Send(pack);
			if (status.GetStatus() != Status::EStatusType::DONE)
			{
				std::cout << "//////////////////// No se ha podido enviar el nombre de la partida ////////////////////" << std::endl;
			}
		}

		*_continueBSS = true;

	} while (!(*_exitBSS));
	std::cout << "Salgo del BSS" << std::endl;
}

int main()
{
	unsigned int localPort = 50000;

	std::vector<TcpSocket*> clientes;
	Selector selector;
	TcpListener listener;

	std::string opc;

	bool exitBSS = false;
	bool continueBSS = false;

	ConnectToBSS(&clientes, &selector, &exitBSS, &continueBSS);

	std::thread tAccepts(ControlPeers, &clientes, &selector, &listener, &exitBSS, &continueBSS);
	tAccepts.detach();

	while (opc != "e")
	{
		std::cout << "Escribe un mensaje:" << std::endl;
		std::getline(std::cin, opc);

		OutputMemoryStream pack;
		
		if (opc != "e")
		{
			pack.Write(static_cast<int>(Protocol::PEER_PEERProtocol::SENDMESSAGE));
			pack.WriteString(opc);
			
			for (size_t i = 0; i < clientes.size(); i++)
			{
				Status status = (clientes.at(i))->Send(pack);
				if (status.GetStatus() != Status::EStatusType::DONE)
				{
					std::cout << "El mensaje enviado Peer2Peer no se ha enviado: " << std::endl;
				}
			}

		}
	} 

	return 0;
}
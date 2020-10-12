#include "Network.h"
#include <iostream>

Network::Network(asio::io_context& IoContext, unsigned short Port, std::function<std::vector<std::string>(std::shared_ptr<OwnCharacter>, const BaseClientPacket&)> CbRetrieveCharacter,
	std::function<void(OwnCharacter)> CbDisconnectCharacter)
	: ioContext(IoContext)
	, acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Port))
	, started(false)
	, lastConnectionId(1)
	, cbRetrieveCharacter(CbRetrieveCharacter)
	, cbDisconnectCharacter(CbDisconnectCharacter)
{

}

Network::~Network()
{

}

void Network::startServer()
{
	if (!started)
	{
		startAccept();
		started = true;
	}
}

void Network::sendPacketBroadcast(const std::string& Packet)
{
	std::cout << "Broadcasted : " << Packet << std::endl;
	for (auto it = connections.begin(); it != connections.end(); ++it)
		it->second->sendPacket(Packet);
}

void Network::sendPacketTo(const std::vector<int>& connectionsId, const std::string& Packet)
{
	for (int it : connectionsId)
	{
		if (connections.find(it) != connections.end())
			connections.at(it)->sendPacket(Packet);
	}
}

std::vector<OwnCharacter> Network::getConnectedCharacters() const
{
	std::vector<OwnCharacter> characters;
	for (auto character : connections)
	{
		characters.push_back(character.second->getConnectedCharacter());
	}
	return characters;
}

void Network::startAccept()
{
	std::shared_ptr<Connection> connection = Connection::create(ioContext);
	acceptor.async_accept(connection->getSocket(), std::bind(&Network::onAccept, this, connection, std::placeholders::_1));
}

void Network::onAccept(std::shared_ptr<Connection> connection, const asio::error_code& error)
{
	if (!error)
	{
		connections.insert(std::pair<int, std::shared_ptr<Connection>>(lastConnectionId, connection));
		connection->setDisconnectionCallback(std::bind(&Network::onDisconnection, this, lastConnectionId)); // Not sure about the last argument, wtf did I do ?
		connection->setRetrieveCharacterCallback(cbRetrieveCharacter);
		connection->setConnectionId(lastConnectionId);
		lastConnectionId++;
		connection->start();
	}
	startAccept();
}

void Network::onDisconnection(int connectionId)
{
	OwnCharacter removedChar = connections.at(connectionId)->getConnectedCharacter();
	std::cout << "Erased : " << connectionId << std::endl;
	connections.erase(connectionId);
	cbDisconnectCharacter(removedChar);
}

#include "Network.h"

#include <iostream>

Network::Network(asio::io_context& IoContext, unsigned short Port)
	: ioContext(IoContext)
	, acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Port))
	, started(false)
	, lastConnectionId(1)
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

void Network::startAccept()
{
	std::shared_ptr<Connection> connection = Connection::create(ioContext);
	acceptor.async_accept(connection->getSocket(), std::bind(&Network::onAccept, this, connection, std::placeholders::_1));
}

void Network::onAccept(std::shared_ptr<Connection> connection, const asio::error_code& error)
{
	if (!error)
	{
		connections.insert(std::pair<size_t, std::shared_ptr<Connection>>(lastConnectionId, connection));
		connection->setDisconnectionCallback(std::bind(&Network::onDisconnection, this, lastConnectionId));
		connection->setConnectionId(lastConnectionId);
		lastConnectionId++;
		connection->start();
	}
	startAccept();
}

void Network::onDisconnection(size_t connectionId)
{
	std::cout << "Erased : " << connectionId << std::endl;

	for (int i = 0; i < connections.size(); i++)
	{
		std::vector<int> key, value;
		for (std::map<size_t, std::shared_ptr<Connection>>::iterator it = connections.begin(); it != connections.end(); ++it) {
			key.push_back(it->first);
			std::cout << "Key: " << it->first << std::endl;
		}
	}
	connections.erase(connectionId);
	for (int i = 0; i < connections.size(); i++)
	{
		std::vector<int> key, value;
		for (std::map<size_t, std::shared_ptr<Connection>>::iterator it = connections.begin(); it != connections.end(); ++it) {
			key.push_back(it->first);
			std::cout << "Key: " << it->first << std::endl;
		}
	}
}

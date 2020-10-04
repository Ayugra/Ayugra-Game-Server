#pragma once

#include "Connection.h"
#include <map>

class Network
{
public:
	Network(asio::io_context& IoContext, unsigned short Port, std::function<void(std::shared_ptr<OwnCharacter>)> CbRetrieveCharacter);
	~Network();
	void startServer();
	void sendPacketBroadcast(const std::string& Packet);
	void sendPacketTo(const std::vector<int>& connectionsId, const std::string& Packet);
	std::vector<OwnCharacter> getConnectedCharacters() const;

private:
	void startAccept();
	void onAccept(std::shared_ptr<Connection> connection, const asio::error_code& error);
	void onDisconnection(int connection);

	asio::io_context& ioContext;
	asio::ip::tcp::acceptor acceptor;
	bool started;
	int lastConnectionId;
	std::map<int, std::shared_ptr<Connection>> connections;

	std::function<void(std::shared_ptr<OwnCharacter>)> cbRetrieveCharacter;
};

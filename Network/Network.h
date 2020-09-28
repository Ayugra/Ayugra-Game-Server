#pragma once

#include "Connection.h"
#include <map>

class Network
{
public:
	Network(asio::io_context& IoContext, unsigned short Port);
	~Network();
	void startServer();

private:
	void startAccept();
	void onAccept(std::shared_ptr<Connection> connection, const asio::error_code& error);
	void onDisconnection(size_t connection);

	asio::io_context& ioContext;
	asio::ip::tcp::acceptor acceptor;
	bool started;
	size_t lastConnectionId;
	std::map<size_t, std::shared_ptr<Connection>> connections;
};

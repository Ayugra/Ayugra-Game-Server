#pragma once

#include <asio.hpp>
#include "Utils.h"
#include "Client.h"
#include "Database/DatabaseManager.h"

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	~Connection();
	static std::shared_ptr<Connection> create(asio::io_context& IoContext);
	asio::ip::tcp::socket& getSocket();
	void start();
	void sendPacket(const std::string& Packet);
	void setConnectionId(int ConnectionId);
	int getConnectionId() const;
	OwnCharacter getConnectedCharacter() const;


	// Signals & Slots system
	void setDisconnectionCallback(std::function<void(int)> CbDisconnect);
	void setRetrieveCharacterCallback(std::function<void(std::shared_ptr<OwnCharacter>)> CbRetrieveCharacter);

private:
	Connection(asio::io_context& IoContext);
	void startReading();
	void onWrite(const asio::error_code& error, size_t bytes);
	void onRead(const asio::error_code& error, size_t bytes);
	void disconnect();
	std::vector<std::string> isPacketProcessable(std::string Packet);
	bool checkEncryptionKey();

	asio::ip::tcp::socket socket;
	char packetBuffer[64];
	std::string packet;
	bool started;
	int encryptionKey;
	unsigned short packetId;
	int connectionId;
	Client client;
	bool disconnected;


	// Signals & Slots system
	std::function<void(int)> cbDisconnect;
	std::function<void(std::shared_ptr<OwnCharacter>)> cbRetrieveCharacter;
};

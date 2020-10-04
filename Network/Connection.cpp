#include "Connection.h"
#include "Cryptography/Cryptography.h"
#include <iostream>

Connection::Connection(asio::io_context& IoContext)
	: socket(IoContext)
	, started(false)
	, packetBuffer("")
	, packetId(0)
	, encryptionKey(-1)
	, packet("")
	, connectionId(0)
	, client(std::bind(&Connection::sendPacket, this, std::placeholders::_1), std::bind(&Connection::disconnect, this))
	, disconnected(false)
{
	memset(packetBuffer, 0, 64);
}

Connection::~Connection()
{
	DatabaseManager::call("p_disconnect", { SQL_TYPE::INT, std::to_string(client.getAccountId()) });
	socket.shutdown(asio::ip::tcp::socket::shutdown_both);
	socket.close();
	std::cout << "Connection::~Connection();" << std::endl;
}

std::shared_ptr<Connection> Connection::create(asio::io_context& IoContext)
{
	return std::shared_ptr<Connection>(new Connection(IoContext));
}

asio::ip::tcp::socket& Connection::getSocket()
{
	return socket;
}

void Connection::start()
{
	if (!started)
	{
		startReading();
		started = true;
	}
}

void Connection::sendPacket(const std::string& Packet)
{
	if (disconnected)
		return;
	std::cout << "Sent : " << Packet << std::endl;
	std::string* copy = new std::string(Cryptography::WorldEncrypt(Packet));
	if (copy == nullptr)
		return;
	asio::async_write(socket, asio::buffer(*copy), [self = shared_from_this(), copy](const asio::error_code& error, size_t bytes)
	{
		self->onWrite(error, bytes);
		if (copy != nullptr)
			delete copy;
	});
}

void Connection::setConnectionId(int ConnectionId)
{
	connectionId = ConnectionId;
	client.setConnectionId(ConnectionId);
}

int Connection::getConnectionId() const
{
	return connectionId;
}

OwnCharacter Connection::getConnectedCharacter() const
{
	return client.getConnectedCharacter();
}

void Connection::setDisconnectionCallback(std::function<void(int)> CbDisconnect)
{
	cbDisconnect = CbDisconnect;
}

void Connection::setRetrieveCharacterCallback(std::function<void(std::shared_ptr<OwnCharacter>)> CbRetrieveCharacter)
{
	cbRetrieveCharacter = CbRetrieveCharacter;
	client.setRetrieveCharacterCallback(CbRetrieveCharacter);
}

void Connection::startReading()
{
	if (disconnected)
		return;
	socket.async_receive(asio::buffer(packetBuffer), [self = shared_from_this()](const asio::error_code& error, size_t bytes)
	{ self->onRead(error, bytes); });
}

void Connection::onWrite(const asio::error_code& error, size_t bytes)
{
	if (error)
	{
		std::cout << "WRITE : " << error.message() << " size : " << bytes << std::endl;
	}
	// Maybe add the msg to make something out of it ? but what
}

void Connection::onRead(const asio::error_code& error, size_t bytes)
{
	if (error)
	{
		std::cerr << "Connection::onRead() ERROR : " << error.message() <<
			" bytes received : " << bytes << std::endl;
		disconnect();
		return;
	}
	if (bytes > 0)
	{
		std::string tmp = std::string(packetBuffer, sizeof(packetBuffer));
		memset(packetBuffer, 0, sizeof(packetBuffer));
		tmp.erase(tmp.find_last_not_of('\x00') + 1, std::string::npos);
		packet += tmp;
		std::string readPacket;
		while (!packet.empty() && !(readPacket = Cryptography::WorldDecrypt(&packet, encryptionKey, encryptionKey == -1)).empty())
		{
			std::cout << "Read : " << readPacket << std::endl;
			std::vector<std::string> packs;
			if ((packs = isPacketProcessable(readPacket)).empty())
				continue;
			client.dispatchPacket(packs);
		}
	}
	startReading();
}

void Connection::disconnect()
{
	disconnected = true;
	cbDisconnect(connectionId);
}

std::vector<std::string> Connection::isPacketProcessable(std::string Packet)
{
	size_t spacePos = Packet.find_first_of(" ");
	if (spacePos == std::string::npos)
	{
		std::cerr << "Connection::isPacketProcessable(1) WARNING : packet with size == ("
			<< Packet.size() << ") - value : [" << Packet << "]" << std::endl;
		disconnect();
		return {};
	}
	if (encryptionKey == -1)
	{
		packetId = ToNumber<unsigned short>(Packet.c_str());
		encryptionKey = ToNumber<int>(Packet.erase(0, Packet.find_first_of(" ") + 1).c_str());
		if (packetId == 0 || encryptionKey == 0)
		{
			std::cerr << "Connection::isPacketProcessable(1) WARNING : packet with size == ("
				<< Packet.size() << ") - value : [" << Packet << "]" << std::endl;
			disconnect();
		}
		client.setEncryptionKey(encryptionKey);
		return {};
	}
	std::vector<std::string> packs = split(Packet.erase(0, Packet.find_first_of(" ")), " ");
	return packs;
}

bool Connection::checkEncryptionKey()
{
	return false;
}

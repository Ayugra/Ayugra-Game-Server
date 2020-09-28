#include "Client.h"
#include <iostream>

Client::Client(std::function<void(std::string)> CbSendPacket, std::function<void()> CbDisconnect)
	: cbSendPacket(CbSendPacket)
	, cbDisconnect(CbDisconnect)
	, account(CbDisconnect)
{

}

Client::~Client()
{

}

void Client::setEncryptionKey(int EncryptionKey)
{
	account.setEncryptionKey(EncryptionKey);
}

int Client::getAccountId() const
{
	return account.getAccountId();
}

void Client::dispatchPacket(const BaseClientPacket& Packet)
{

	// Handle all this code in a thread pool


	std::vector<std::string> response;
	response = account.handlePacket(Packet);
	if (!response.empty())
	{
		sendPacket(response);
		return;
	}


}

void Client::sendPacket(std::vector<std::string> response)
{
	if(response.empty())
		return;
	for (auto&& resp : response)
		cbSendPacket(resp);
}

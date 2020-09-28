#pragma once

#include <functional>
#include "Game/Accounts/Account.h"
#include "Network/Packets/BaseServerPacket.h"

class Client
{
public: // Signals & Slots system
	Client(std::function<void(std::string)> CbSendPacket, std::function<void()> CbDisconnect);
	~Client();

	void setEncryptionKey(int EncryptionKey);
	int getAccountId() const;

	void dispatchPacket(const BaseClientPacket& Packet);

private:
	void sendPacket(std::vector<std::string> response);

	Account account;

	// Signals & Slots system
	std::function<void(std::string)> cbSendPacket;
	std::function<void()> cbDisconnect;
};

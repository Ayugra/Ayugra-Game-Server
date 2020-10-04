#pragma once

#include <functional>
#include "Game/Accounts/Account.h"
#include "Game/Accounts/Character/OwnCharacter.h"
#include "Packets/Client/R_game_start.h"

class Client
{
public: // Signals & Slots system
	Client(std::function<void(std::string)> CbSendPacket, std::function<void()> CbDisconnect);
	~Client();

	void setEncryptionKey(int EncryptionKey);
	void setConnectionId(int ConnectionId);
	int getConnectionId() const;
	int getAccountId() const;
	OwnCharacter getConnectedCharacter() const;

	void dispatchPacket(const BaseClientPacket& Packet);


	// Signals & Slots system
	void setRetrieveCharacterCallback(std::function<void(std::shared_ptr<OwnCharacter>)> CbRetrieveCharacter);

private:
	void sendPacket(std::vector<std::string> response);

	std::vector<std::string> handlePacket(const BaseClientPacket& Packet);
	std::vector<std::string> handle_game_start(const R_game_start& Packet);

	Account account;
	int connectionId;
	OwnCharacter character;

	// Signals & Slots system
	std::function<void(std::string)> cbSendPacket;
	std::function<void()> cbDisconnect;
	std::function<void(std::shared_ptr<OwnCharacter>)> cbRetrieveCharacter;
};

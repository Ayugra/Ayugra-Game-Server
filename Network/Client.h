#pragma once
#include "Game/Accounts/Account.h"
#include "Game/Accounts/Character/OwnCharacter.h"
#include "Packets/Client/R_game_start.h"
#include "Packets/Client/Map/R_preq.h"
#include "Packets/Client/Inventory/R_eqinfo.h"

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
	void setRetrieveCharacterCallback(std::function<std::vector<std::string>(std::shared_ptr<OwnCharacter>, const BaseClientPacket&)> CbRetrieveCharacter);

private:
	void sendPacket(std::vector<std::string> response);

	std::vector<std::string> handlePacket(const BaseClientPacket& Packet);
	std::vector<std::string> handle_game_start(const R_game_start& Packet);
	std::vector<std::string> handle_eqinfo(const R_eqinfo& Packet);

	Account account;
	int connectionId;
	std::shared_ptr<OwnCharacter> character;

	// Signals & Slots system
	std::function<void(std::string)> cbSendPacket;
	std::function<void()> cbDisconnect;
	std::function<std::vector<std::string>(std::shared_ptr<OwnCharacter>, const BaseClientPacket&)> cbRetrieveCharacter;
};

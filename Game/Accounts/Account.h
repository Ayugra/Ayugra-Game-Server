#pragma once

#include <map>
#include <functional>
#include "Database/DatabaseManager.h"
#include "Game/Accounts/LobbyCharacters/LobbyCharacter.h"
#include "Network/Packets/Client/Lobby/R_UsernamePacket.h"
#include "Network/Packets/Client/Lobby/R_PasswordPacket.h"
#include "Network/Packets/Client/Lobby/R_Char_NEW.h"
#include "Network/Packets/Client/Lobby/R_Char_NEW_JOB.h"
#include "Network/Packets/Client/Lobby/R_Char_DEL.h"
#include "Network/Packets/Client/Lobby/R_Char_REN.h"
#include "Network/Packets/Client/Lobby/R_select.h"

class Account
{
public:
	Account(std::function<void()> CbDisconnect);
	~Account();

	void setEncryptionKey(int EncryptionKey);

	std::string getUsername() const;
	std::string getPassword() const;
	int getAccountId() const;
	int getSelectedCharacterId() const;
	int getAuthority() const;
	LobbyCharacter getSelectedLobbyCharacter() const;

	bool isConnected() const { return connected; }
	void setConnectionId(int ConnectionId);
	int getConnectionId() const;

	std::vector<std::string> handlePacket(const BaseClientPacket& Packet);

private:
	std::vector<std::string> handleUsernamePacket(const R_UsernamePacket& Packet);
	std::vector<std::string> handlePasswordPacket(const R_PasswordPacket& Packet);
	std::vector<std::string> handle_Char_NEW_JOB(const R_Char_NEW_JOB& Packet);
	std::vector<std::string> handle_Char_NEW(const R_Char_NEW& Packet);
	std::vector<std::string> handle_Char_DEL(const R_Char_DEL& Packet);
	std::vector<std::string> handle_Char_REN(const R_Char_REN& Packet);
	std::vector<std::string> handle_select(const R_select& Packet);

	std::vector<std::string> loadLobbyCharacters(short selected = -1);
	bool connectAccount();
	bool createCharacter(const R_Char_NEW& Packet, ClassType charClass);
	bool deleteCharacter(short slot);

	bool connected;
	int accountId;
	int encryptionKey;
	int authority;
	std::string username;
	std::string password;
	LangType lang;
	std::map<short, LobbyCharacter> lobbyCharacters;
	short selectedSlot;
	int connectionId;
	
	
	// Signals & Slots system
	std::function<void()> cbDisconnect;
};

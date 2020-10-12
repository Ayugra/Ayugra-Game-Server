#pragma once
#include <functional>
#include "Game/Accounts/LobbyCharacters/LobbyCharacter.h"
#include "Game/Accounts/Character/Attributes/Reputation.h"
#include "Game/Accounts/Character/Attributes/Position.h"
#include "Game/Accounts/Character/Attributes/Level.h"
#include "Game/Accounts/Character/Attributes/Inventory/Inventory.h"

class OwnCharacter
{
public:
	OwnCharacter() : id(-1) {}
	OwnCharacter(const LobbyCharacter& lobChar, std::function<void(std::string)> CbSendPacket);

	void sendPacket(std::string Packet)
	{
		cbSendPacket(Packet);
	}

	void changeMap(int mapId, int mapX, int mapY);
	void walk(int x, int y);

	int getId() const { return id; }
	std::string getPseudonym() const { return pseudonym; }
	ClassType getClass() const { return charClass; }
	short getSlot() const { return slot; }
	GenderType getGender() const { return gender; }
	HairStyleType getHairStyle() const { return hairStyle; }
	int getHairColor() const { return hairColor; }
	bool getRename() const { return rename; }
	std::string getWornStuff() const { return wornStuff; }
	short getQuestAct() const { return questAct; }
	short getQuestChapter() const { return questAct; }
	std::string getPetSet() const { return petSet; }
	Reputation getReputationProperties() const { return reputation; }
	Position getPositionProperties() const { return position; }
	Level getLevelProperties() const { return level; }
	Inventory getInventory() const { return inventory; }
	int getAuthority() const { return authority; }


	std::string pseudonym;

private:
	void loadLevelProperties(int levelN, int levelJ, int levelH);
	void loadReputationProperties();
	void loadPositionProperties();

	/*
	class Morph
	haircolor
	hairstyle
	morphid
	*/
	int authority;
	int id;
	Reputation reputation;
	Position position;
	Level level;
	Inventory inventory;
	short slot;
	GenderType gender;
	HairStyleType hairStyle;
	int hairColor;
	ClassType charClass;
	bool rename;
	std::string wornStuff;
	short questAct;
	short questChapter;
	std::string petSet;


	std::function<void(std::string)> cbSendPacket;
};

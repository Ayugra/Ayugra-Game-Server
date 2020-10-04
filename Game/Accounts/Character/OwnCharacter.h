#pragma once

#include "Game/Accounts/LobbyCharacters/LobbyCharacter.h"
#include "Game/Accounts/Character/Attributes/Reputation.h"
#include "Game/Accounts/Character/Attributes/Position.h"
#include "Game/Accounts/Character/Attributes/Level.h"

class OwnCharacter
{
public:
	OwnCharacter() : id(-1) {}
	OwnCharacter(const LobbyCharacter& lobChar);

	/*
	Packets handler ?
	*/

	int getId() const							{ return id; }
	std::string getPseudonym() const			{ return pseudonym; }
	ClassType getClass() const					{ return charClass; }
	short getSlot() const						{ return slot; }
	GenderType getGender() const				{ return gender; }
	HairStyleType getHairStyle() const			{ return hairStyle; }
	int getHairColor() const					{ return hairColor; }
	bool getRename() const						{ return rename; }
	std::string getWornStuff() const			{ return wornStuff; }
	short getQuestAct() const					{ return questAct; }
	short getQuestChapter() const				{ return questAct; }
	std::string getPetSet() const				{ return petSet; }
	Reputation getReputationProperties() const	{ return reputation; }
	Position getPositionProperties() const		{ return position; }
	Level getLevelProperties() const			{ return level; }

private:
	void loadLevelProperties(int levelN, int levelJ, int levelH);
	void loadReputationProperties();
	void loadPositionProperties();

	Reputation reputation;
	Position position;
	Level level;
	int id;
	std::string pseudonym;
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
};

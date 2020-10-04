#pragma once

#include <string>
#include "Game/Types/ClassType.h"
#include "Game/Types/HairStyleType.h"
#include "Game/Types/GenderType.h"

class LobbyCharacter
{
public:
	LobbyCharacter()
		: id(-1)
		, pseudonym("")
		, slot(-1)
		, gender(GenderType::MALE)
		, hairStyle(HairStyleType::NOHAIR)
		, hairColor(-1)
		, charClass(ClassType::ADVENTURER)
		, level(-1)
		, levelHero(-1)
		, levelJob(-1)
		, rename(false)
		, wornStuff("-1.-1.-1.-1.-1.-1.-1.-1.-1.-1")
		, questAct(-1)
		, questChapter(-1)
		, petSet("-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.")
		, connectionId(-1)
		, valid(false)
	{}

	LobbyCharacter(int Id, std::string Pseudonym, short Slot, GenderType Gender, HairStyleType HairStyle, int HairColor, ClassType CharClass,
		int Level, int LevelHero, int LevelJob, bool Rename, std::string WornStuff, short QuestAct, short QuestChapter, std::string PetSet)
		: id(Id)
		, pseudonym(Pseudonym)
		, slot(Slot)
		, gender(Gender)
		, hairStyle(HairStyle)
		, hairColor(HairColor)
		, charClass(CharClass)
		, level(Level)
		, levelHero(LevelHero)
		, levelJob(LevelJob)
		, rename(Rename)
		, wornStuff(WornStuff)
		, questAct(QuestAct)
		, questChapter(QuestChapter)
		, petSet(PetSet)
		, connectionId(-1)
		, valid(true)
	{
		
	}

	std::string getLobbyPacket() const
	{
		std::string p = std::to_string(slot);
		p += " " + pseudonym;
		p += " 0";
		p += " " + std::to_string(static_cast<int>(gender));
		p += " " + std::to_string(static_cast<int>(hairStyle));
		p += " " + std::to_string(hairColor);
		p += " 0";
		p += " " + std::to_string(static_cast<int>(charClass));
		p += " " + std::to_string(level);
		p += " " + std::to_string(levelHero);
		p += " " + wornStuff;
		p += " " + std::to_string(levelJob);
		p += " " + std::to_string(questAct);
		p += " " + std::to_string(questChapter);
		p += " " + petSet;
		p += " -1";
		p += " " + std::to_string(rename);
		return p;
	}

	void changePseudonym(const std::string& newPseudonym)	{ pseudonym = newPseudonym; }
	void setRename(bool Rename)								{ rename = Rename; }

	int getCharacterId() const			{ return id; }
	bool canChangePseudonym() const		{ return rename; }
	std::string getPseudonym() const	{ return pseudonym; }
	short getSlot() const				{ return slot; }
	GenderType getGender() const		{ return gender; }
	HairStyleType getHairStyle() const	{ return hairStyle; }
	int getHairColor() const			{ return hairColor; }
	ClassType getCharClass() const		{ return charClass; }
	int getLevel() const				{ return level; }
	int getLevelHero() const			{ return levelHero; }
	int getLevelJob() const				{ return levelJob; }
	std::string getWornStuff() const	{ return wornStuff; }
	short getQuestAct() const			{ return questAct; }
	short getQuestChapter() const		{ return questChapter; }
	std::string getPetSet() const		{ return petSet; }

	int getConnectionId() const			{ return connectionId; }
	bool isValid() const				{ return valid; }


	void setConnectionId(int ConnectionId) { connectionId = ConnectionId; }

private:
	bool valid;

	int id;
	std::string pseudonym;
	short slot;
	GenderType gender;
	HairStyleType hairStyle;
	int hairColor;
	ClassType charClass;
	int level;
	int levelHero;
	int levelJob;
	bool rename;
	std::string wornStuff;
	short questAct;
	short questChapter;
	std::string petSet;

	int connectionId;
};

#pragma once

#include <string>
#include "Game/ClassType.h"
#include "Game/HairStyleType.h"
#include "Game/GenderType.h"

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

	void changePseudonym(const std::string& newPseudonym)
	{
		pseudonym = newPseudonym;
	}

	int getCharacterId() const
	{
		return id;
	}

	bool canChangePseudonym() const
	{
		return rename;
	}

	void setRename(bool Rename)
	{
		rename = Rename;
	}

	std::string getPseudonym() const
	{
		return pseudonym;
	}

	bool isValid() const
	{
		return valid;
	}

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
};

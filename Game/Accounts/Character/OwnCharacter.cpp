#include "OwnCharacter.h"
#include "Utils.h"
#include "Database/DatabaseManager.h"

OwnCharacter::OwnCharacter(const LobbyCharacter& lobChar, std::function<void(std::string)> CbSendPacket)
	: id(lobChar.getCharacterId())
	, pseudonym(lobChar.getPseudonym())
	, slot(lobChar.getSlot())
	, gender(lobChar.getGender())
	, hairStyle(lobChar.getHairStyle())
	, hairColor(lobChar.getHairColor())
	, charClass(lobChar.getCharClass())
	, rename(lobChar.canChangePseudonym())
	, wornStuff(lobChar.getWornStuff())
	, questAct(lobChar.getQuestAct())
	, questChapter(lobChar.getQuestChapter())
	, petSet(lobChar.getPetSet())
	, authority(lobChar.getAuthority())
	, cbSendPacket(CbSendPacket)
{
	loadLevelProperties(lobChar.getLevel(), lobChar.getLevelJob(), lobChar.getLevelHero());
	loadReputationProperties();
	loadPositionProperties();
	inventory.loadInventory(id);
}

void OwnCharacter::changeMap(int mapId, int mapX, int mapY)
{
	position.mapId = mapId;
	position.posX = mapX;
	position.posY = mapY;
	position.direction = 2;
}

void OwnCharacter::walk(int x, int y)
{
	position.posX = x;
	position.posY = y;
}

void OwnCharacter::loadLevelProperties(int levelN, int levelJ, int levelH)
{
	std::vector<std::vector<std::string>> res = DatabaseManager::call("p_get_experience_info", { SQL_TYPE::INT, std::to_string(id) });
	if (!res.empty() && res[0].size() == 3)
		level = Level(levelN, levelJ, levelH, ToNumber<int>(res[0][0].c_str()), ToNumber<int>(res[0][1].c_str()), ToNumber<int>(res[0][2].c_str()));
}

void OwnCharacter::loadReputationProperties()
{
	std::vector<std::vector<std::string>> res = DatabaseManager::call("p_get_reputation_info", { SQL_TYPE::INT, std::to_string(id) });
	if (!res.empty() && res[0].size() == 3)
	{
		LadderEntity entity(ToNumber<int>(res[0][0].c_str()), level.levelN, level.levelH, pseudonym, id);
		reputation = Reputation(entity.data, ReputationManager::getReputationType(entity),
			ToNumber<int>(res[0][1].c_str()), getDignityType(ToNumber<int>(res[0][1].c_str())), ToNumber<int>(res[0][2].c_str()));
	}
}

void OwnCharacter::loadPositionProperties()
{
	std::vector<std::vector<std::string>>res = DatabaseManager::call("p_get_position_info", { SQL_TYPE::INT, std::to_string(id) });
	if (!res.empty() && res[0].size() == 3)
		position = Position(ToNumber<int>(res[0][0].c_str()), ToNumber<int>(res[0][1].c_str()), ToNumber<int>(res[0][2].c_str()));
}

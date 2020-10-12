#include "CharStatsConfiguration.h"
#include "Utils.h"
#include <rapidjson.h>
#include <filereadstream.h>
#include <cstdio>
#include <filesystem>
#include <iostream>

std::map<ClassType, int> CharStatsConfiguration::speed;
std::map<ClassType, int> CharStatsConfiguration::regenHp;
std::map<ClassType, int> CharStatsConfiguration::regenMp;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::hp;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::mp;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::atk_melee;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::atk_distance;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::atk_magic;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::precision_melee;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::precision_distance;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::def_melee;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::def_distance;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::def_magic;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::dodge_melee;
std::map<ClassType, std::map<int, int>> CharStatsConfiguration::dodge_distance;

CharStatsConfiguration::CharStatsConfiguration()
{
	std::filesystem::path cwd = std::filesystem::current_path();
#ifdef _WIN32
	cwd += "\\character_stats_table.json";
#else
	cwd += "/character_stats_table.json";
#endif
	pathToConfig = cwd.string();
	std::cout << "\nFile : " << pathToConfig << "\n";
}

CharStatsConfiguration::~CharStatsConfiguration()
{
}

bool CharStatsConfiguration::load()
{
	return reload();
}

bool CharStatsConfiguration::reload()
{
	FILE* fp;
#ifdef _WIN32
	errno_t status = fopen_s(&fp, pathToConfig.c_str(), "rb");
#else
	errno_t status = fopen_s(&fp, pathToConfig.c_str(), "r");
#endif
	if (status == 0 && fp != NULL)
	{
		char buffer[4096];
		rapidjson::FileReadStream reader(fp, buffer, sizeof(buffer));
		rapidjson::Document d;
		d.ParseStream(reader);
		if (fp)
			fclose(fp);
		if (!parseConfig(d))
		{
			std::cerr << "Configuration : error (config file has wrong format)\n";
			return false;
		}
	}
	else
	{
		char buffer[128];
		strerror_s(buffer, status);
		std::cerr << "Configuration : error n" << status << " (" << buffer << ")\n";
		return false;
	}
	return true;
}

int CharStatsConfiguration::getSpeed(ClassType classType)
{
	return speed.at(classType);
}

int CharStatsConfiguration::getHPRegen(ClassType classType)
{
	return regenHp.at(classType);
}

int CharStatsConfiguration::getMPRegen(ClassType classType)
{
	return regenMp.at(classType);
}

int CharStatsConfiguration::getBaseHP(ClassType classType, int level)
{
	return hp.at(classType).at(level);
}

int CharStatsConfiguration::getBaseMP(ClassType classType, int level)
{
	return mp.at(classType).at(level);
}

int CharStatsConfiguration::getAtkMelee(ClassType classType, int level)
{
	return atk_melee.at(classType).at(level);
}

int CharStatsConfiguration::getAtkDistance(ClassType classType, int level)
{
	return atk_distance.at(classType).at(level);
}

int CharStatsConfiguration::getAtkDefMagic(ClassType classType, int level)
{
	return atk_magic.at(classType).at(level);
}

int CharStatsConfiguration::getDefMelee(ClassType classType, int level)
{
	return def_melee.at(classType).at(level);
}

int CharStatsConfiguration::getDefDistance(ClassType classType, int level)
{
	return def_distance.at(classType).at(level);
}

int CharStatsConfiguration::getDefMagic(ClassType classType, int level)
{
	return def_magic.at(classType).at(level);
}

int CharStatsConfiguration::getPrecisionMelee(ClassType classType, int level)
{
	return precision_melee.at(classType).at(level);
}

int CharStatsConfiguration::getPrecisionDistance(ClassType classType, int level)
{
	return precision_distance.at(classType).at(level);
}

int CharStatsConfiguration::getDodgeMelee(ClassType classType, int level)
{
	return dodge_melee.at(classType).at(level);
}

int CharStatsConfiguration::getDodgeDistance(ClassType classType, int level)
{
	return dodge_distance.at(classType).at(level);
}

bool CharStatsConfiguration::isConfigValid(const rapidjson::Document& document)
{
	if (!document.IsObject())
		return false;
	if (!document.HasMember("adventurer") || !document["adventurer"].IsObject())
		return false;
	if (!document.HasMember("swordsman") || !document["swordsman"].IsObject())
		return false;
	if (!document.HasMember("archer") || !document["archer"].IsObject())
		return false;
	if (!document.HasMember("magician") || !document["magician"].IsObject())
		return false;
	if (!document.HasMember("martial_artist") || !document["martial_artist"].IsObject())
		return false;
	return true;
}

bool CharStatsConfiguration::parseConfig(const rapidjson::Document& document)
{
	if (!isConfigValid(document))
		return false;

	for (auto& charClass : document.GetObject())
	{
		std::string className = charClass.name.GetString();
		for (auto& charStatCategory : charClass.value.GetObject()) // Speed, RegenHp, Hp, Defense, etc
		{
			ClassType currentClass = ClassType::ADVENTURER;
			if (className == "adventurer")		currentClass = ClassType::ADVENTURER;
			else if (className == "swordsman")		currentClass = ClassType::SWORDSMAN;
			else if (className == "archer")			currentClass = ClassType::ARCHER;
			else if (className == "magician")		currentClass = ClassType::MAGICIAN;
			else if (className == "martial_artist")	currentClass = ClassType::MARTIAL_ARTIST;

			std::string category = charStatCategory.name.GetString(); // Speed, RegenHp, Hp, Defense, etc
			if (category == "speed")
				speed.insert({ currentClass, charStatCategory.value.GetInt() });
			else if (category == "regen_hp")
				regenHp.insert({ currentClass, charStatCategory.value.GetInt() });
			else if (category == "regen_mp")
				regenMp.insert({ currentClass, charStatCategory.value.GetInt() });
			else if (category == "hp" || category == "mp")
			{
				std::map<int, int> levelToValueTmp;
				for (auto& levelValue : charStatCategory.value.GetObject()) // example "1": 221... (hp adventurer)
					levelToValueTmp.insert({ ToNumber<int>(levelValue.name.GetString()), levelValue.value.GetInt() });
				if		(category == "hp") hp.insert({ currentClass, levelToValueTmp });
				else if (category == "mp") mp.insert({ currentClass, levelToValueTmp });
			}
			else
			{
				for (auto& subcategory : charStatCategory.value.GetObject()) // Melee, Distance, Magic
				{
					std::string scategory = subcategory.name.GetString();
					std::map<int, int> levelToValueTmp;
					for (auto& levelValue : subcategory.value.GetObject()) // example "1": 221... (hp adventurer)
						levelToValueTmp.insert({ ToNumber<int>(levelValue.name.GetString()), levelValue.value.GetInt() });
					if (category == "attack")
					{
						if (scategory == "melee")	atk_melee.insert({ currentClass, levelToValueTmp });
						if (scategory == "distance")atk_distance.insert({ currentClass, levelToValueTmp });
						if (scategory == "magic")	atk_magic.insert({ currentClass, levelToValueTmp });
					}
					else if (category == "precision")
					{
						if (scategory == "melee")	precision_melee.insert({ currentClass, levelToValueTmp });
						if (scategory == "distance")precision_distance.insert({ currentClass, levelToValueTmp });
					}
					else if (category == "defense")
					{
						if (scategory == "melee")	def_melee.insert({ currentClass, levelToValueTmp });
						if (scategory == "distance")def_distance.insert({ currentClass, levelToValueTmp });
						if (scategory == "magic")	def_magic.insert({ currentClass, levelToValueTmp });
					}
					else if (category == "dodge")
					{
						if (scategory == "melee")	dodge_melee.insert({ currentClass, levelToValueTmp });
						if (scategory == "distance")dodge_distance.insert({ currentClass, levelToValueTmp });
					}
				}
			}
		}
	}
	return true;
}

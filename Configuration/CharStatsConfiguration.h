#pragma once

#include "Game/Types/ClassType.h"
#include <document.h>
#include <string>
#include <map>

class CharStatsConfiguration
{
public:
	CharStatsConfiguration();
	~CharStatsConfiguration();
	bool load();
	bool reload();

	static int getSpeed(ClassType classType);
	static int getHPRegen(ClassType classType);
	static int getMPRegen(ClassType classType);

	static int getBaseHP(ClassType classType, int level);
	static int getBaseMP(ClassType classType, int level);

	static int getAtkMelee(ClassType classType, int level);
	static int getAtkDistance(ClassType classType, int level);
	static int getAtkDefMagic(ClassType classType, int level);

	static int getDefMelee(ClassType classType, int level);
	static int getDefDistance(ClassType classType, int level);
	static int getDefMagic(ClassType classType, int level);

	static int getPrecisionMelee(ClassType classType, int level);
	static int getPrecisionDistance(ClassType classType, int level);

	static int getDodgeMelee(ClassType classType, int level);
	static int getDodgeDistance(ClassType classType, int level);

private:
	bool isConfigValid(const rapidjson::Document& document);
	bool parseConfig(const rapidjson::Document& document);

	std::string pathToConfig;

	static std::map<ClassType, int> speed;
	static std::map<ClassType, int> regenHp;
	static std::map<ClassType, int> regenMp;

	static std::map<ClassType, std::map<int, int>> hp;
	static std::map<ClassType, std::map<int, int>> mp;

	static std::map<ClassType, std::map<int, int>> atk_melee;
	static std::map<ClassType, std::map<int, int>> atk_distance;
	static std::map<ClassType, std::map<int, int>> atk_magic;

	static std::map<ClassType, std::map<int, int>> precision_melee;
	static std::map<ClassType, std::map<int, int>> precision_distance;

	static std::map<ClassType, std::map<int, int>> def_melee;
	static std::map<ClassType, std::map<int, int>> def_distance;
	static std::map<ClassType, std::map<int, int>> def_magic;

	static std::map<ClassType, std::map<int, int>> dodge_melee;
	static std::map<ClassType, std::map<int, int>> dodge_distance;
};

/*
speed   
regen_hp
        regen_mp
        hp
        mp
        attack
        precision
        defense
        dodge
*/
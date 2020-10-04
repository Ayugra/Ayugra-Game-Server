#pragma once

#include <document.h>
#include <string>
#include <map>

enum class XpType
{
	NORMAL = 1,
	JOB_ADVENTURER = 2,
	JOB = 3,
	HERO = 4,
	PRIMARY_SP = 5,
	SECONDARY_SP = 6,
	PET = 7,
	PARTNER = 8,
	FAIRY = 9,
	FAMILY = 10
};

class XpConfiguration
{
public:
	XpConfiguration();
	~XpConfiguration();
	bool load();
	bool reload();

	static int getXpNeeded(XpType xpType, int level);

private:
	bool isConfigValid(const rapidjson::Document& document);
	bool parseConfig(const rapidjson::Document& document);

	std::string pathToConfig;

	static std::map<XpType, std::map<int, int>> xpTypeMapper;
	static std::map<int, int> xp_normal;
	static std::map<int, int> xp_job_adventurer;
	static std::map<int, int> xp_job;
	static std::map<int, int> xp_hero;
	static std::map<int, int> xp_primary_sp;
	static std::map<int, int> xp_secondary_sp;
	static std::map<int, int> xp_pet;
	static std::map<int, int> xp_partner;
	static std::map<int, int> xp_fairy;
	static std::map<int, int> xp_family;
};
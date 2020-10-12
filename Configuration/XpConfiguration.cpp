#include "XpConfiguration.h"
#include "Utils.h"
#include <rapidjson.h>
#include <filereadstream.h>
#include <cstdio>
#include <filesystem>
#include <iostream>

std::map<XpType, std::map<int, int>> XpConfiguration::xpTypeMapper;
std::map<int, int> XpConfiguration::xp_normal;
std::map<int, int> XpConfiguration::xp_job_adventurer;
std::map<int, int> XpConfiguration::xp_job;
std::map<int, int> XpConfiguration::xp_hero;
std::map<int, int> XpConfiguration::xp_primary_sp;
std::map<int, int> XpConfiguration::xp_secondary_sp;
std::map<int, int> XpConfiguration::xp_pet;
std::map<int, int> XpConfiguration::xp_partner;
std::map<int, int> XpConfiguration::xp_fairy;
std::map<int, int> XpConfiguration::xp_family;

XpConfiguration::XpConfiguration()
{
	std::filesystem::path cwd = std::filesystem::current_path();
#ifdef _WIN32
	cwd += "\\xp_table.json";
#else
	cwd += "/xp_table.json";
#endif
	pathToConfig = cwd.string();
	std::cout << "\nFile : " << pathToConfig << "\n";
}

XpConfiguration::~XpConfiguration()
{
}

bool XpConfiguration::load()
{
	return reload();
}

bool XpConfiguration::reload()
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

int XpConfiguration::getXpNeeded(XpType xpType, int level)
{
	if (xpTypeMapper.find(xpType) == xpTypeMapper.end())
		return 0;
	std::map<int, int> curr = xpTypeMapper.at(xpType);
	if (curr.find(level) == curr.end())
		return 0;
	return curr.at(level);
}

bool XpConfiguration::isConfigValid(const rapidjson::Document& document)
{
	if (!document.IsObject())
		return false;
	if (!document.HasMember("normal") || !document["normal"].IsObject())
		return false;
	if (!document.HasMember("job_adventurer") || !document["job_adventurer"].IsObject())
		return false;
	if (!document.HasMember("job") || !document["job"].IsObject())
		return false;
	if (!document.HasMember("hero") || !document["hero"].IsObject())
		return false;
	if (!document.HasMember("primary_sp") || !document["primary_sp"].IsObject())
		return false;
	if (!document.HasMember("secondary_sp") || !document["secondary_sp"].IsObject())
		return false;
	if (!document.HasMember("pet") || !document["pet"].IsObject())
		return false;
	if (!document.HasMember("partner") || !document["partner"].IsObject())
		return false;
	if (!document.HasMember("fairy") || !document["fairy"].IsObject())
		return false;
	if (!document.HasMember("family") || !document["family"].IsObject())
		return false;
	return true;
}

bool XpConfiguration::parseConfig(const rapidjson::Document& document)
{
	if (!isConfigValid(document))
		return false;

	for (auto& m : document.GetObject())
	{
		std::string category = m.name.GetString();
		for (auto& m2 : m.value.GetObject())
		{
			if (category == "normal")
				xp_normal.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "job_adventurer")
				xp_job_adventurer.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "job")
				xp_job.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "hero")
				xp_hero.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "primary_sp")
				xp_primary_sp.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "secondary_sp")
				xp_secondary_sp.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "pet")
				xp_pet.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "partner")
				xp_partner.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "fairy")
				xp_fairy.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
			else if (category == "family")
				xp_family.insert({ ToNumber<int>(m2.name.GetString()), m2.value.GetInt() });
		}
	}

	xpTypeMapper.insert({ XpType::NORMAL, xp_normal });
	xpTypeMapper.insert({ XpType::JOB_ADVENTURER, xp_job_adventurer });
	xpTypeMapper.insert({ XpType::JOB, xp_job });
	xpTypeMapper.insert({ XpType::HERO, xp_hero });
	xpTypeMapper.insert({ XpType::PRIMARY_SP, xp_primary_sp });
	xpTypeMapper.insert({ XpType::SECONDARY_SP, xp_secondary_sp });
	xpTypeMapper.insert({ XpType::PET, xp_pet });
	xpTypeMapper.insert({ XpType::PARTNER, xp_partner });
	xpTypeMapper.insert({ XpType::FAIRY, xp_fairy });
	xpTypeMapper.insert({ XpType::FAMILY, xp_family });

	return true;
}

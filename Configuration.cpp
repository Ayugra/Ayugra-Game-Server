#include "Configuration.h"
#include <rapidjson.h>
#include <filereadstream.h>
#include <cstdio>
#include <filesystem>
#include <iostream>

int Configuration::server_id;
int Configuration::server_channel_id;
unsigned short Configuration::server_port;

Configuration::Configuration()
{
	std::filesystem::path cwd = std::filesystem::current_path();
#ifdef _WIN32
	cwd += "\\ServGame_config.json";
#else
	cwd += "/ServGame_config.json";
#endif
	pathToConfig = cwd.string();
	std::cout << "\nFile : " << pathToConfig << "\n";
}

Configuration::~Configuration()
{
}

bool Configuration::load()
{
	return reload();
}

bool Configuration::reload()
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
		char buffer[100];
		strerror_s(buffer, status);
		std::cerr << "Configuration : error n" << status << " (" << buffer << ")\n";
		return false;
	}
	return true;
}

bool Configuration::isConfigValid(const rapidjson::Document& document)
{
	if (!document.IsObject())
		return false;

	if (!document.HasMember("server") || !document["server"].IsObject())
		return false;
	{
		const rapidjson::Value& server = document["server"];
		if (!server.HasMember("id") || !server["id"].IsInt())
			return false;
		if (!server.HasMember("channel_id") || !server["channel_id"].IsInt())
			return false;
		if (!server.HasMember("port") || !server["port"].IsInt())
			return false;
	}

	if (!document.HasMember("database") || !document["database"].IsObject())
		return false;
	{
		const rapidjson::Value& database = document["database"];
		if (!database.HasMember("port") || !database["port"].IsInt())
			return false;
		if (!database.HasMember("host") || !database["host"].IsString())
			return false;
		if (!database.HasMember("username") || !database["username"].IsString())
			return false;
		if (!database.HasMember("password") || !database["password"].IsString())
			return false;
		if (!database.HasMember("database") || !database["database"].IsString())
			return false;
	}

	return true;
}

bool Configuration::parseConfig(const rapidjson::Document& document)
{
	if (!isConfigValid(document))
		return false;

	{
		server_id			= document["server"]["id"].GetInt();
		server_channel_id	= document["server"]["channel_id"].GetInt();
		server_port			= document["server"]["port"].GetInt();
	}


	{
		database_port		= document["database"]["port"].GetInt();
		database_host		= document["database"]["host"].GetString();
		database_username	= document["database"]["username"].GetString();
		database_password	= document["database"]["password"].GetString();
		database_database	= document["database"]["database"].GetString();
	}

	return true;
}

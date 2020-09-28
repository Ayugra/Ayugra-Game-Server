#pragma once

#include <document.h>
#include <string>

/*{
 	"server":
	{
		"server_id": (int) server id,
		"channel_id": (int) channel id,
		"port": (unsigned short) port used to create the server
	},
	"database":
	{
		"port": (unsigned short) port used for MySQL
		"host": (std::string) host used to connect to the database
		"username": (std::string) username used to connect to the database
		"password": (std::string) password used to connect to the database
		"database": (std::string) database to connect to
	}
}*/

class Configuration
{
public:
	Configuration();
	~Configuration();
	bool load();
	bool reload();

	static int d_server_id() { return server_id; }
	static int d_channel_id() { return server_channel_id; }
	static unsigned short d_server_port() { return server_port; }

	unsigned short d_database_port() const { return database_port; }
	std::string d_database_host() const { return database_host; }
	std::string d_database_username() const { return database_username; }
	std::string d_database_password() const { return database_password; }
	std::string d_database_database() const { return database_database; }

private:
	bool isConfigValid(const rapidjson::Document& document);
	bool parseConfig(const rapidjson::Document& document);

	std::string pathToConfig;

	static int server_id;
	static int server_channel_id;
	static unsigned short server_port;

	unsigned short database_port;
	std::string database_host;
	std::string database_username;
	std::string database_password;
	std::string database_database;
};
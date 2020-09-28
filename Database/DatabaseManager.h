#pragma once

#include <mysql.h>
#include <vector>
#include <string>

enum class SQL_TYPE
{
	INT,
	STRING
};

class DatabaseManager
{
public:
	DatabaseManager(std::string Host, std::string Username, std::string Password, std::string Database, unsigned short Port, bool Connect = true);
	~DatabaseManager();

	static std::vector<std::vector<std::string>> query(const std::string& query, int maxNbIteration);
	static std::vector<std::string> query(const std::string& query);
	static bool call(const std::string& functionName, const std::vector<std::pair<SQL_TYPE, std::string>>& args);
	static std::vector<std::vector<std::string>> selectFunction(const std::string& functionName, const std::vector<std::pair<SQL_TYPE, std::string>>& args);

	bool connect();
	bool disconnect();
	bool loadPreparedStatements();

private:
	static MYSQL* connection;
	static std::vector<MYSQL_STMT*> stmt;
	std::string host;
	std::string username;
	std::string password;
	std::string database;
	unsigned short port;
};

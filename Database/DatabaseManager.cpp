#include "DatabaseManager.h"
#include <iostream>
#include "Utils.h"

MYSQL* DatabaseManager::connection;
std::vector<MYSQL_STMT*> DatabaseManager::stmt;

DatabaseManager::DatabaseManager(std::string Host, std::string Username, std::string Password, std::string Database, unsigned short Port, bool Connect)
	: host(Host)
	, username(Username)
	, password(Password)
	, database(Database)
	, port(Port)
{
	if (Connect)
		connect();
}

DatabaseManager::~DatabaseManager()
{
	std::cout << "DatabaseManager::~DatabaseManager();";
}

// Is there a race condition in this function when it is used by 2 threads ?
std::vector<std::vector<std::string>> DatabaseManager::query(const std::string& query, int maxNbIteration)
{
	if (!connection)
		return {};
	if (mysql_query(connection, query.c_str()))
		return {};
	MYSQL_RES* res = mysql_store_result(connection);
	if (!res)
		return {};
	std::vector<std::vector<std::string>> output;
	MYSQL_ROW row;
	int it = 0;
	while ((row = mysql_fetch_row(res)) && (it < maxNbIteration || maxNbIteration == -1))
	{
		if (row[0] == nullptr)
			break;
		std::vector<std::string> tmp;
		for (size_t i = 0; i < res->field_count; i++)
			tmp.push_back(row[i]); // Populate by columns
		output.push_back(tmp); // Populate by rows
		it++;
	}
	while (mysql_more_results(connection))
		mysql_next_result(connection);
	mysql_free_result(res);
	return output;
}

std::vector<std::string> DatabaseManager::query(const std::string& query)
{
	if (!connection)
		return {};
	if (mysql_query(connection, query.c_str()))
		return {};
	MYSQL_RES* res = mysql_store_result(connection);
	if (!res)
		return {};
	std::vector<std::string> output;
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row)
	{
		for (size_t i = 0; i < res->field_count; i++)
			output.push_back(row[i]);
	}
	while (mysql_more_results(connection))
		mysql_next_result(connection);
	mysql_free_result(res);
	return output;
}

std::vector<std::vector<std::string>> DatabaseManager::call(const std::string& functionName, const std::vector<std::pair<SQL_TYPE, std::string>>& args)
{
	if (!connection)
		return {};
	std::string query = "CALL " + functionName + "(";
	for (size_t i = 0; i < args.size(); i++)
	{
		std::pair<SQL_TYPE, std::string> current = args[i];
		if (current.first == SQL_TYPE::INT)
			query += current.second;
		else if (current.first == SQL_TYPE::STRING)
			query += "\'" + current.second + "\'";
		else
			return {};
		if (i < args.size() - 1)
			query += ", ";
	}
	query += ");";
	if (mysql_query(connection, query.c_str()))
	{
		std::cout << mysql_errno(connection);
		return {};
	}
	MYSQL_RES* res = mysql_store_result(connection);
	if (!res)
		return {};
	std::vector<std::vector<std::string>> output;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		if (row[0] == nullptr)
			break;
		std::vector<std::string> tmp;
		for (size_t i = 0; i < res->field_count; i++)
			tmp.push_back(row[i]); // Populate by columns
		output.push_back(tmp); // Populate by rows
	}
	while (mysql_more_results(connection))
		mysql_next_result(connection);
	mysql_free_result(res);
	return output;
}

std::vector<std::vector<std::string>> DatabaseManager::call(const std::string& functionName, const std::pair<SQL_TYPE, std::string>& args)
{
	if (!connection)
		return {};
	std::string query = "CALL " + functionName + "(";
	if (args.first == SQL_TYPE::INT)
		query += args.second;
	else if (args.first == SQL_TYPE::STRING)
		query += "\'" + args.second + "\'";
	else
		return {};
	query += ");";
	if (mysql_query(connection, query.c_str()))
		return {};
	MYSQL_RES* res = mysql_store_result(connection);
	if (!res)
		return {};
	std::vector<std::vector<std::string>> output;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		if (row[0] == nullptr)
			break;
		std::vector<std::string> tmp;
		for (size_t i = 0; i < res->field_count; i++)
			tmp.push_back(row[i]); // Populate by columns
		output.push_back(tmp); // Populate by rows
	}
	while (mysql_more_results(connection))
		mysql_next_result(connection);
	mysql_free_result(res);
	return output;
}

std::vector<std::vector<std::string>> DatabaseManager::selectFunction(const std::string& functionName, const std::vector<std::pair<SQL_TYPE, std::string>>& args)
{
	if (!connection)
		return {};
	std::string query = "SELECT " + functionName + "(";
	for (size_t i = 0; i < args.size(); i++)
	{
		std::pair<SQL_TYPE, std::string> current = args[i];
		if (current.first == SQL_TYPE::INT)
			query += current.second;
		else if (current.first == SQL_TYPE::STRING)
			query += "\'" + current.second + "\'";
		else
			return {};
		if (i < args.size() - 1)
			query += ", ";
	}
	query += ");";
	if (mysql_query(connection, query.c_str()))
		return {};
	MYSQL_RES* res = mysql_store_result(connection);
	if (!res)
		return {};
	std::vector<std::vector<std::string>> output;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		if (row[0] == nullptr)
			break;
		std::vector<std::string> tmp;
		for (size_t i = 0; i < mysql_num_fields(res); i++)
			tmp.push_back(row[i]); // Populate by columns
		output.push_back(tmp); // Populate by rows
	}
	while (mysql_more_results(connection))
		mysql_next_result(connection);
	mysql_free_result(res);
	return output;
}

bool DatabaseManager::connect()
{
	connection = mysql_init(0);
	connection = mysql_real_connect(connection, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, NULL, 0);
	if (!connection)
		std::cerr << "Error : Failed to connect to database\n";
	return connection;
}

bool DatabaseManager::disconnect()
{
	return false;
}

bool DatabaseManager::loadPreparedStatements()
{
	return false;
}

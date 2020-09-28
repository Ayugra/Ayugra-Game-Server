#include "Network/Network.h"
#include "Database/DatabaseManager.h"
#include "Configuration.h"
#include <iostream>

void startServerConnection()
{
	asio::io_context io_context;
	Network server(io_context, Configuration::d_server_port());
	server.startServer();
	io_context.run();
}

/*	auto t1 = std::chrono::high_resolution_clock::now();

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); // 3017
	std::cout << duration;
*/

int main()
{
	Configuration conf;
	while (!conf.load())
	{
		std::cout << "Config not loaded" << std::endl;
		Sleep(2000);
	}

	DatabaseManager dbMng(conf.d_database_host(), conf.d_database_username(), conf.d_database_password(), conf.d_database_database(),
		conf.d_database_port());

	std::thread networkThread(&startServerConnection);
	while (true)
	{
		Sleep(2000);
	}
	return 0;
}
#include <iostream>
#include "Engine.h"

/*	auto t1 = std::chrono::high_resolution_clock::now();

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); // µs
	std::cout << duration;
*/



#include "Configuration/XpConfiguration.h"
#include "Configuration/CharStatsConfiguration.h"
#include "Configuration/GameFiles/ItemDatParser.h"
int main()
{
	ItemDat itemDat("Item.dat", "_code_fr_Item.txt", 65536 /*to add in conf*/);
	while (!itemDat.startParsing())
	{
		std::cout << "Item.dat not loaded... Retry in 5s" << std::endl;
		Sleep(5000);
	}
	std::cout << "Item.dat successfully loaded." << std::endl;
	
	XpConfiguration XpConfig;
	while (!XpConfig.load())
	{
		std::cout << "xp_table.json not loaded... Retry in 5s" << std::endl;
		Sleep(5000);
	}

	CharStatsConfiguration CharStatsConfig;
	while (!CharStatsConfig.load())
	{
		std::cout << "character_stats_table.json not loaded... Retry in 5s" << std::endl;
		Sleep(5000);
	}

	ServerConfiguration Config;
	while (!Config.load())
	{
		std::cout << "ServGame_config.json not loaded... Retry in 5s" << std::endl;
		Sleep(5000);
	}
	DatabaseManager dbMng(Config.d_database_host(), Config.d_database_username(), Config.d_database_password(), Config.d_database_database(), Config.d_database_port());
	asio::io_context io_context;
	Engine engine(io_context, Config);
	engine.start();

	while (true)
	{
		Sleep(2000);
	}
	return 0;
}

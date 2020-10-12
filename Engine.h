#pragma once
#include "Network/Network.h"
#include "Database/DatabaseManager.h"
#include "Configuration/ServerConfiguration.h"
#include <iostream>
#include "Game/UIManager/Ladder/ReputationManager.h"
#include "Game/UIManager/Ladder/Act4PointsManager.h"
#include "Game/UIManager/Ladder/ComplimentManager.h"
#include "World/World.h"

class Engine
{
public:
	Engine(asio::io_context& IoContext, ServerConfiguration Config);
	~Engine();

	void start();
	std::vector<std::string> retrieveCharacter(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet);
	void disconnectCharacter(const OwnCharacter& character);

private:
	void startServerConnection();

	void initReputationLadder();
	void initComplimentLadder();
	void initAct4pointsLadder();

	Network network;
	ServerConfiguration config;
	asio::io_context& netIo;
	std::thread netThread;
	World world;
};


/*
void startServerConnection()
{
	asio::io_context io_context;
	Network server(io_context, Configuration::d_server_port());
	server.startServer();
	io_context.run();
}





Configuration conf;
	while (!conf.load())
	{
		std::cout << "Config not loaded" << std::endl;
		Sleep(2000);
	}

	DatabaseManager dbMng(conf.d_database_host(), conf.d_database_username(), conf.d_database_password(), conf.d_database_database(),
		conf.d_database_port());

	std::thread networkThread(&startServerConnection);
*/
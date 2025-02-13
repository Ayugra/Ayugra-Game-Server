#include "Engine.h"

Engine::Engine(asio::io_context& IoContext, ServerConfiguration Config)
	: netIo(IoContext)
	, network(IoContext, Config.d_server_port(), [this](std::shared_ptr<OwnCharacter> Character, const BaseClientPacket& Packet)
	{
		return retrieveCharacter(Character, Packet);
	}, [this](OwnCharacter character)
	{
		disconnectCharacter(character);
	})
	, config(Config)
{
	DatabaseManager::call("p_disconnect", { SQL_TYPE::INT, "1" }); // Used for test, remove later

	initReputationLadder();
	initAct4pointsLadder();
	initComplimentLadder();
}

Engine::~Engine()
{
}

void Engine::start()
{
	netThread = std::thread(&Engine::startServerConnection, this);
}

std::vector<std::string> Engine::retrieveCharacter(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& Packet)
{
	std::vector<std::string> packets;
	packets.push_back("stat 500 1000 600 800 1 32");
	if (world.handlePacket(character, Packet, packets) > 0) // >0 or >=0 ? Still need to determinate my needs
		return packets;
	return {};
}

void Engine::disconnectCharacter(const OwnCharacter& character)
{
	world.disconnectCharacter(character);
}

void Engine::startServerConnection()
{
	network.startServer();
	netIo.run();
}

void Engine::initReputationLadder()
{
	std::vector<std::vector<std::string>> output = DatabaseManager::call("p_get_reputation_character_ladder", { SQL_TYPE::INT, std::to_string(ServerConfiguration::d_server_id()) });
	std::vector<LadderEntity> data;
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i].size() != 5)
			break;
		data.insert(data.begin(), LadderEntity(ToNumber<int>(output[i][1].c_str()), ToNumber<int>(output[i][3].c_str()),
			ToNumber<int>(output[i][4].c_str()), output[i][2], ToNumber<int>(output[i][0].c_str())));
	}
	ReputationManager::setReputationLadder(data);
}

void Engine::initComplimentLadder()
{
	std::vector<std::vector<std::string>> output = DatabaseManager::call("p_get_compliments_character_ladder", { SQL_TYPE::INT, std::to_string(ServerConfiguration::d_server_id()) });
	std::vector<LadderEntity> data;
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i].size() != 5)
			break;
		data.insert(data.begin(), LadderEntity(ToNumber<int>(output[i][1].c_str()), ToNumber<int>(output[i][3].c_str()),
			ToNumber<int>(output[i][4].c_str()), output[i][2], ToNumber<int>(output[i][0].c_str())));
	}
	ComplimentManager::setComplimentLadder(data);
}

void Engine::initAct4pointsLadder()
{
	std::vector<std::vector<std::string>> output = DatabaseManager::call("p_get_act4points_character_ladder", { SQL_TYPE::INT, std::to_string(ServerConfiguration::d_server_id()) });
	std::vector<LadderEntity> data;
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i].size() != 5)
			break;
		data.insert(data.begin(), LadderEntity(ToNumber<int>(output[i][1].c_str()), ToNumber<int>(output[i][3].c_str()),
			ToNumber<int>(output[i][4].c_str()), output[i][2], ToNumber<int>(output[i][0].c_str())));
	}
	Act4PointsManager::setAct4pointsLadder(data);
}
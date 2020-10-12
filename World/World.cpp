#include "World.h"
#include "Database/DatabaseManager.h"
#include "Utils.h"
#include <iostream>

World::World()
{
	std::vector<std::vector<std::string>> res = DatabaseManager::call("p_get_maps", { {} });
	for (int i = 0; i < res.size(); i++)
	{
		int mapId = ToNumber<int>(res[i][0].c_str());
		maps.insert({ mapId, Map(mapId) });
	}
}

int World::handlePacket(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets)
{
	if (maps.find(character->getPositionProperties().mapId) == maps.end()) // Check if mapid exists in map pool
		return -1;
	if (packet.getHeader() == "game_start")
		return handle_game_start(character, packet, packets);
	else if (packet.getHeader() == "preq")
		return handle_preq(character, packet, packets);
	else if (packet.getHeader() == "walk")
		return handle_walk(character, packet, packets);
	return 1;
}

void World::disconnectCharacter(const OwnCharacter& character)
{
	int mapId = character.getPositionProperties().mapId;
	if (maps.find(mapId) == maps.end())
		return;
	maps.at(mapId).disconnectPlayer(character);
}

int World::handle_game_start(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets)
{
	int status = maps.at(character->getPositionProperties().mapId).handle_game_start(character, packet, packets);
	if (status < 0) // <= 0 ?
		return status;
	return 1;
}

int World::handle_preq(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets)
{
	int status = maps.at(character->getPositionProperties().mapId).handle_preq(character, packet, packets);
	if (status < 0) // <= 0 ?
		return status;
	status = maps.at(character->getPositionProperties().mapId).handle_game_start(character, packet, packets);
	if (status < 0)
		return status;
	return 1;
}

int World::handle_walk(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets)
{
	int status = maps.at(character->getPositionProperties().mapId).handle_walk(character, packet, packets);
	if (status < 0) // <= 0 ?
		return status;
	return 1;
}

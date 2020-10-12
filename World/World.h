#pragma once
#include <string>
#include "World/Map/Map.h"

class World
{
public:
	World();
	int handlePacket(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets);
	void disconnectCharacter(const OwnCharacter& character);

private:
	int handle_game_start(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets);
	int handle_preq(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets);
	int handle_walk(std::shared_ptr<OwnCharacter> character, const BaseClientPacket& packet, std::vector<std::string>& packets);

	std::map<int, Map> maps;
};

#pragma once
#include <map>
#include <vector>
#include "Game/Entities/Portal.h"
#include "Game/Accounts/Character/OwnCharacter.h"
#include "Network/Packets/BaseClientPacket.h"
#include "Network/Packets/Client/Map/R_walk.h"
#include "Network/Packets/Client/R_game_start.h"
#include "Network/Packets/Client/Map/R_preq.h"

class Map
{
public:
	Map(int MapId);
	~Map();

	void attachPortal(Portal portal);
	void detachPortal(int id);
	void detachPortal(Portal portal);

	bool attachPlayer(std::shared_ptr<OwnCharacter> character);
	void detachPlayer(int characterId);
	void detachPlayer(std::shared_ptr<OwnCharacter> character);
	void disconnectPlayer(const OwnCharacter& character);

	int handle_game_start(std::shared_ptr<OwnCharacter> character, const R_game_start& packet, std::vector<std::string>& resp);
	int handle_preq(std::shared_ptr<OwnCharacter> character, const R_preq& packet, std::vector<std::string>& resp);
	int handle_walk(std::shared_ptr<OwnCharacter> character, const R_walk& packet, std::vector<std::string>& resp);

private:
	// idea : can use return type for handling some kind of things (such as disconnection, as example)


	int generateCharacterPopPacket(std::shared_ptr<OwnCharacter> character, std::vector<std::string>& resp);
	int generatePortalsPacket(std::vector<std::string>& resp);

	int mapId;
	// std::map<int, Monster> monsters;
	std::map<int, Portal> portals;
	// std::map<int, NPC> npcs;
	std::map<int, std::shared_ptr<OwnCharacter>> players;
	// mapgrid
};

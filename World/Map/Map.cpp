#include "Map.h"
#include "Database/DatabaseManager.h"
#include "Configuration/XpConfiguration.h"
#include "Utils.h"
#include "Pathfinding/PathfindingUtils.h"
#include "Network/Packets/Server/Map/S_at.h"
#include "Network/Packets/Server/Map/S_c_map.h"
#include "Network/Packets/Server/Map/S_gp.h"
#include "Network/Packets/Server/Map/S_mapout.h"
#include "Network/Packets/Server/Character/S_c_mode.h"
#include "Network/Packets/Server/Character/S_c_info.h"
#include "Network/Packets/Server/Character/Inventory/S_equip.h"
#include "Network/Packets/Server/Character/S_lev.h"
#include <iostream>

Map::Map(int MapId)
	: mapId(MapId)
{
	auto res = DatabaseManager::call("p_get_map_portals", { { SQL_TYPE::INT, std::to_string(MapId) } });
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i].size() != 10)
			continue;
		Portal portal(i/*ToInt(res[i][0])*/, ToInt(res[i][1]), ToInt(res[i][2]), ToInt(res[i][3]), ToInt(res[i][4]), ToInt(res[i][5]),
			ToInt(res[i][6]), ToInt(res[i][7]), ToInt(res[i][8]), static_cast<PortalType>(ToInt(res[i][9])));
		portals.insert({ portal.getEntityID(), portal });
	}
}

Map::~Map()
{

}

void Map::attachPortal(Portal portal)
{
	if (portals.contains(portal.getEntityID()))
	portals.insert({ portal.getEntityID(), portal });
}

void Map::detachPortal(int id)
{
	if (portals.find(id) == portals.end())
		return;
	portals.erase(id);
}

void Map::detachPortal(Portal portal)
{
	detachPortal(portal.getEntityID());
}

bool Map::attachPlayer(std::shared_ptr<OwnCharacter> character)
{
	if (!players.contains(character->getId()))
	{
		players.insert({ character->getId(), character });
		return true;
	}
	return false;
}

void Map::detachPlayer(int characterId)
{
	if (players.contains(characterId))
		players.erase(characterId);
}

void Map::detachPlayer(std::shared_ptr<OwnCharacter> character)
{
	detachPlayer(character->getId());
}

void Map::disconnectPlayer(const OwnCharacter& character)
{
	// Generate out packet
	players.erase(character.getId());
}

int Map::handle_game_start(std::shared_ptr<OwnCharacter> character, const R_game_start& packet, std::vector<std::string>& resp)
{
	return generateCharacterPopPacket(character, resp);
}

/* Return value :
* >0 : mapId to go to
* -1 : no portal in range (< 2)
* -2 : wait before taking portal (already took one in last second)
* -3 : portal closed
* -4 : players not on the map
* add not enough reputation
* add no familly
* and other thing not allowing to go in
*/
int Map::handle_preq(std::shared_ptr<OwnCharacter> character, const R_preq& packet, std::vector<std::string>& resp)
{
	if (players.find(character->getId()) == players.end())
		return -4;
	for (auto& portal : portals)
	{
		if (distance(character->getPositionProperties().posX, character->getPositionProperties().posY,
			portal.second.getX(), portal.second.getY()) < 2)
		{
			if (portal.second.isInvisible())
				continue;
			//	if (character->getPositionProperties->lastPortalTaken - now() < 2500) // smthing like that
			//		return -2;
			//	Check some others conditions... (closed, portalType, etc)
			//		return ...;
			// generate out packet for other players if there is at least one
			// and stop monsters from moving after 15s
			resp.push_back(S_c_map(0, character->getPositionProperties().mapId, false).getPacketString());
			resp.push_back(S_mapout().getPacketString());

			if (portal.second.getDestMapId() != mapId)
			{
				detachPlayer(character); // Profile is there is a race condition between the detach and attach time
				// If yes, change the following code :
				character->changeMap(portal.second.getDestMapId(), portal.second.getDestMapX(), portal.second.getDestMapY());
				// send out packet to other players
			}
			else
			{
				// We're on the same map, the portal has for dest map = this map
				// so just send tp packet to character and to players[all]
			}
			return portal.second.getDestMapId();
		}
	}
	return -1;
}

/* Return value :
* -1 : packet not valid
* -2 : speed not valid
* -3 : step too high
* -4 : distance traveled too high
* -5 : try to walk on unwalkable cell
*/
int Map::handle_walk(std::shared_ptr<OwnCharacter> character, const R_walk& packet, std::vector<std::string>& resp)
{
	if (!packet.isValid())
		return -1;
	// Add grid check
	// Add speed check but need to check if he walked after the last cond packet (but with ping...)
	double dist = distance(character->getPositionProperties().posX, character->getPositionProperties().posY, packet.getX(), packet.getY());
	if (dist > (float)(packet.getSpeed() / 2.5f) + 1)
	{
		std::cout << "Walk denied : " << packet.getPacketString() << std::endl;
		return -3;
	}
	character->walk(packet.getX(), packet.getY());
		// int step = static_cast<int>(std::ceil(static_cast<float>(speed/2.5f) - 1));
		// float time = step * 2500 / speed;
}

int Map::generateCharacterPopPacket(std::shared_ptr<OwnCharacter> character, std::vector<std::string>& resp)
{
	if (!attachPlayer(character))
		return -1;
	resp.push_back(S_c_info(*character).getPacketString());
	resp.push_back(S_c_mode(*character).getPacketString());
	resp.push_back(S_equip(character->getInventory().getWornStuff().getMappedItems()).getPacketString());
	resp.push_back(S_lev(*character).getPacketString());
	resp.push_back(S_at(character->getId(), character->getPositionProperties().mapId, character->getPositionProperties().posX,
		character->getPositionProperties().posY, character->getPositionProperties().direction, 0, 0, 1, -1).getPacketString()); // TODO : music and unk
	// Titinfo packet
	// Eq packet
	resp.push_back(S_c_map(0, character->getPositionProperties().mapId, true).getPacketString());
	// Send the in packet to other players
	generatePortalsPacket(resp);
	return 1;
}

int Map::generatePortalsPacket(std::vector<std::string>& resp)
{
	for (const auto& portal : portals)
	{
		if (!portal.second.isInvisible())
			resp.push_back(S_gp(portal.second).getPacketString());
	}
	return 1;
}

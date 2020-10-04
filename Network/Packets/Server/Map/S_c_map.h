#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_c_map : public BaseServerPacket
{
public:
	S_c_map(int unknown, int mapId, bool isEntering)
		: BaseServerPacket("c_map")
	{
		packet += " " + std::to_string(unknown);
		packet += " " + std::to_string(mapId);
		packet += " " + std::to_string(isEntering);
	}
};

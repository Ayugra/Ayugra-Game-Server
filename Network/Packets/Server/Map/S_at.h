#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_at : public BaseServerPacket
{
public:
	S_at(int characterId, int mapId, int posX, int posY, int direction, int unk1, int musicId, int unk2, int unk3)
		: BaseServerPacket("at")
	{
		packet += " " + std::to_string(characterId);
		packet += " " + std::to_string(mapId);
		packet += " " + std::to_string(posX);
		packet += " " + std::to_string(posY);
		packet += " " + std::to_string(direction);
		packet += " " + std::to_string(unk1);
		packet += " " + std::to_string(musicId);
		packet += " " + std::to_string(unk2);
		packet += " " + std::to_string(unk3);
	}
};

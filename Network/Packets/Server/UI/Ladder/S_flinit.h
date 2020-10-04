#pragma once
#include <vector>
#include "Network/Packets/BaseServerPacket.h"
#include "Game/UIManager/Ladder/LadderEntity.h"

class S_flinit : public BaseServerPacket
{
public:
	S_flinit(std::vector<LadderEntity> entities)
		: BaseServerPacket("flinit")
	{
		for (int i = (int)entities.size() - 1; i >= 0; i--)
		{
			packet += " " + std::to_string(entities[i].id)
					+ "|" + std::to_string(entities[i].level)
					+ "|" + std::to_string(entities[i].levelH)
					+ "|" + std::to_string(entities[i].data)
					+ "|" + entities[i].pseudonym;
		}
	}
};

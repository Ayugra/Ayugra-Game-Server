#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Game/Types/ReputationType.h"
#include "Game/Types/DignityType.h"

class S_fd : public BaseServerPacket
{
public:
	S_fd(int reputationAmount, ReputationType reputationIcon, int dignityAmount, DignityType dignityIcon)
		: BaseServerPacket("fd")
	{
		packet += " " + std::to_string(reputationAmount);
		packet += " " + std::to_string(static_cast<int>(reputationIcon));
		packet += " " + std::to_string(dignityAmount);
		packet += " " + std::to_string(static_cast<int>(dignityIcon));
	}
};

#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_clist_start : public BaseServerPacket
{
public:
	S_clist_start(int value)
		: BaseServerPacket("clist_start")
	{
		packet += " " + std::to_string(value);
	}
};
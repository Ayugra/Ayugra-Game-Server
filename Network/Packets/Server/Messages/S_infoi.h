#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_infoi : public BaseServerPacket
{
public:
	S_infoi(int msgId, int arg1, int arg2, int arg3)
		: BaseServerPacket("infoi")
	{
		packet += " " + std::to_string(msgId);
		packet += " " + std::to_string(arg1);
		packet += " " + std::to_string(arg2);
		packet += " " + std::to_string(arg3);
	}
};

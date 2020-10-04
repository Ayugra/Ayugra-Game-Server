#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_c_info_reset : public BaseServerPacket
{
public:
	S_c_info_reset()
		: BaseServerPacket("c_info_reset")
	{

	}
};
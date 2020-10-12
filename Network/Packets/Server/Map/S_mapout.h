#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_mapout : public BaseServerPacket
{
public:
	S_mapout()
		: BaseServerPacket("mapout")
	{

	}
};
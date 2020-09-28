#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_OKs : public BaseServerPacket
{
public:
	S_OKs()
		: BaseServerPacket("OK")
	{

	}
};
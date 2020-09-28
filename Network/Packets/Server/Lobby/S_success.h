#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_success : public BaseServerPacket
{
public:
	S_success()
		: BaseServerPacket("success")
	{

	}
};
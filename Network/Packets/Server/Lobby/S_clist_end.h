#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_clist_end : public BaseServerPacket
{
public:
	S_clist_end(int charSelected = -1)
		: BaseServerPacket("clist_end")
	{
		if (charSelected != -1)
			packet += " " + std::to_string(charSelected);
	}
};
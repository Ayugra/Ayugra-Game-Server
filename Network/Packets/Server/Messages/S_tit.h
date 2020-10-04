#pragma once

#include "Network/Packets/BaseServerPacket.h"

class S_tit : public BaseServerPacket
{
public:
	S_tit(int classId, std::string pseudonym)
		: BaseServerPacket("tit")
	{
		packet += " " + std::to_string(classId);
		packet += " " + pseudonym;
	}
};

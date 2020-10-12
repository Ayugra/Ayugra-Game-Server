#pragma once

#include "Network/Packets/BaseClientPacket.h"

class R_preq : public BaseClientPacket
{
public:
	R_preq(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() == 1)
		{
			valid = true;
		}
	}

	bool isValid() const { return valid; }

private:
	bool valid;
};

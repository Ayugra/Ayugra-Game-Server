#pragma once

#include "Network/Packets/BaseClientPacket.h"

class R_select : public BaseClientPacket
{
public:
	R_select(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() == 2)
		{
			slot = ToNumber<short>(packets[1].c_str());
			valid = slot >= 0 && slot <= 3;
		}
	}

	bool isValid() const	{ return valid; }

	short getSlot() const	{ return slot; }


private:
	bool valid;

	short slot;
};

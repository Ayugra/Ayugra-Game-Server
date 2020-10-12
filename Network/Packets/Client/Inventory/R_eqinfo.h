#pragma once
// eqinfo {InvSlotDifferent} {Slot}
#include "Network/Packets/BaseClientPacket.h"

class R_eqinfo : public BaseClientPacket
{
public:
	R_eqinfo(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() == 3)
		{
			inventorySlot = ToNumber<int>(packets[1].c_str());
			slot = ToNumber<int>(packets[2].c_str());
			valid = true;
		}
	}

	bool isValid() const { return valid; }

	int getInventorySlot() const { return inventorySlot; }
	int getSlot() const { return slot; }

private:
	bool valid;
	int inventorySlot;
	int slot;
};

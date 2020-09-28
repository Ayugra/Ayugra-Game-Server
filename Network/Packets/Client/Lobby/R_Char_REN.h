#pragma once

#include "Network/Packets/BaseClientPacket.h"
#include "ForbiddenString.h"

class R_Char_REN : public BaseClientPacket
{
public:
	R_Char_REN(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() >= 3)
		{
			slot = ToNumber<short>(packets[1].c_str());
			pseudonym = packets[2];
			valid = (slot >= 0 && slot <= 3) && pseudonym.find_first_not_of(ALLOWED_CHAR_USERNAME) == std::string::npos;
		}
	}

	bool isValid() const { return valid; }

	std::string getPseudonym() const { return pseudonym; }
	short getSlot() const { return slot; }

private:
	bool valid;

	std::string pseudonym;
	short slot;
};

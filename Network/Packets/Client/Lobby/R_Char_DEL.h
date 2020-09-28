#pragma once

#include "Network/Packets/BaseClientPacket.h"
#include "ForbiddenString.h"

class R_Char_DEL : public BaseClientPacket
{
public:
	R_Char_DEL(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() >= 3)
		{
			slot = ToNumber<short>(packets[1].c_str());
			username = packets[2];
			valid = (slot >= 0 && slot <= 3) && username.find_first_not_of(ALLOWED_CHAR_USERNAME) == std::string::npos;
		}
	}

	bool isValid() const			{ return valid; }

	std::string getUsername() const	{ return username; }
	short getSlot() const			{ return slot; }

private:
	bool valid;

	std::string username;
	short slot;
};

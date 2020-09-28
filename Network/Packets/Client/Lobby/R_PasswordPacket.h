#pragma once

#include "Network/Packets/BaseClientPacket.h"

class R_PasswordPacket : public BaseClientPacket
{
public:
	R_PasswordPacket(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
	{
		if (packets.size() == 1)
		{
			password = packets[0];
		}
	}

	std::string getPassword() const
	{
		return password;
	}

private:
	std::string password;
};
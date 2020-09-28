#pragma once

#include "Network/Packets/BaseClientPacket.h"
#include "Game/LangType.h"

class R_UsernamePacket : public BaseClientPacket
{
public:
	R_UsernamePacket(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, lang(LangType::EN)
	{
		if (packets.size() == 3)
		{
			username = packets[0];
			connectionGFString = packets[1];
			lang = static_cast<LangType>(ToNumber<int>(packets[2].c_str()));
		}
	}

	std::string getUsername() const
	{
		return username;
	}

	std::string getConnectionGFString() const
	{
		return connectionGFString;
	}

	LangType getLang() const
	{
		return lang;
	}

private:
	std::string username;
	std::string connectionGFString;
	LangType lang;
};
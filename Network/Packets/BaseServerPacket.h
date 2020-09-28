#pragma once

#include <string>

class BaseServerPacket
{
public:
	BaseServerPacket() {}

	BaseServerPacket(std::string header)
		: packet(header)
	{

	}

	~BaseServerPacket() {}

	std::string getPacketString()
	{
		return packet;
	}

protected:
	std::string packet;
};
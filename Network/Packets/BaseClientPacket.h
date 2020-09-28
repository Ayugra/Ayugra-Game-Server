#pragma once

#include "Utils.h"
#include <vector>
#include <string>

class BaseClientPacket
{
public:
	BaseClientPacket() {}

	BaseClientPacket(std::vector<std::string> Packets)
		: packets(Packets)
	{
		
	}

	~BaseClientPacket() {}

	std::string getPacketString() const
	{
		return join(packets, " ");
	}

	std::string getHeader() const
	{
		return packets.at(0);
	}

protected:
	std::vector<std::string> packets;
};
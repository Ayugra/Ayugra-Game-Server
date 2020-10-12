#pragma once
// walk 52 50 0 10
#include "Network/Packets/BaseClientPacket.h"

class R_walk : public BaseClientPacket
{
public:
	R_walk(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() == 5)
		{
			x = ToNumber<int>(packets[1].c_str());
			y = ToNumber<int>(packets[2].c_str());
			checksum = ToNumber<int>(packets[3].c_str());
			speed = ToNumber<int>(packets[4].c_str());
			if ((x + y) % 3 % 2 != checksum)
				valid = false;
			else
			{
				if (x < 0 || y < 0 || x > 300 || y > 300)
					valid = false;
				else valid = true;
			}
		}
	}

	bool isValid() const { return valid; }

	int getX() const { return x; }
	int getY() const { return y; }
	int getChecksum() const { return checksum; }
	int getSpeed() const { return speed; }

private:
	bool valid;
	int x;
	int y;
	int checksum;
	int speed;
};



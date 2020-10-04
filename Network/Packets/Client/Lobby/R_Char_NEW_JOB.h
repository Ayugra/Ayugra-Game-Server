#pragma once

#include "Network/Packets/BaseClientPacket.h"
#include "Game/Types/GenderType.h"
#include "Game/Types/HairStyleType.h"
#include "ForbiddenString.h"

class R_Char_NEW_JOB : public BaseClientPacket
{
public:
	R_Char_NEW_JOB(BaseClientPacket bcPacket)
		: BaseClientPacket(bcPacket)
		, valid(false)
	{
		if (packets.size() == 6)
		{
			pseudonym = packets[1];
			slot = ToNumber<short>(packets[2].c_str());
			gender = static_cast<GenderType>(ToNumber<short>(packets[3].c_str()));
			hairStyle = static_cast<HairStyleType>(ToNumber<short>(packets[4].c_str()));
			if (hairStyle != HairStyleType::HAIRSTYLE_A)
				valid = false;
			hairColor = ToNumber<short>(packets[5].c_str());
			valid = (isPseudonymAllowed(pseudonym) == 0) && (slot >= 0 && slot <= 3) && (hairColor >= 0 && hairColor <= 9);
		}
	}

	bool isValid() const				{ return valid; }

	std::string getPseudonym() const	{ return pseudonym; }
	short getSlot() const				{ return slot; }
	GenderType getGender() const		{ return gender; }
	HairStyleType getHairStyle() const	{ return hairStyle; }
	short getHairColor() const			{ return hairColor; }


private:
	bool valid;

	std::string pseudonym;
	short slot;
	GenderType gender;
	HairStyleType hairStyle;
	short hairColor;
};

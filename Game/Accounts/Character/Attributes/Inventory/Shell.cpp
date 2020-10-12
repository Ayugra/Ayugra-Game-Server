#include "Shell.h"
#include "Utils.h"

Shell::Shell(int Rarity, std::vector<ShellEffect> Effects, StuffType StuffType)
	: effects(Effects)
	, stuffType(StuffType)
	, data("")
	, rarity(Rarity)
{
	for (size_t i = 0; i < Effects.size(); i++)
	{
		data += std::to_string(static_cast<int>(Effects[i].getGrade()));
		if (stuffType == StuffType::ARMOR)
			data += std::to_string(static_cast<int>(Effects[i].getArmorEffect()));
		else if (stuffType == StuffType::WEAPON)
			data += std::to_string(static_cast<int>(Effects[i].getWeaponEffect()));
		data += std::to_string(static_cast<int>(Effects[i].getValue()));
	}
}

Shell::Shell(int Rarity, std::string Data, StuffType StuffType)
	: stuffType(StuffType)
	, data(Data)
	, rarity(Rarity)
{
	std::vector<std::string> eff = split(Data, " ");
	for (size_t i = 0; i < eff.size(); i++)
	{
		std::vector<std::string> effVal = split(eff[i], ".");
		if (effVal.size() != 3)
			continue;
		if (stuffType == StuffType::ARMOR)
		{
			effects.push_back(ShellEffect
			(
				static_cast<ShellGradeType>(ToNumber<int>(effVal[0].c_str())),
				static_cast<ShellArmorEffectType>(ToNumber<int>(effVal[1].c_str())),
				ToNumber<int>(effVal[2].c_str())
			));
		}
		else if (stuffType == StuffType::WEAPON)
		{
			effects.push_back(ShellEffect
			(
				static_cast<ShellGradeType>(ToNumber<int>(effVal[0].c_str())),
				static_cast<ShellWeaponEffectType>(ToNumber<int>(effVal[1].c_str())),
				ToNumber<int>(effVal[2].c_str())
			));
		}
	}
}

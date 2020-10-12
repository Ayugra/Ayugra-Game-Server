#pragma once
#include <vector>
#include <string>
#include "Game/Accounts/Character/Attributes/Inventory/ShellEffect.h"

class Shell
{
public:
	Shell() : data(""), rarity(0), stuffType(StuffType::ARMOR) {}
	Shell(int Rarity, std::vector<ShellEffect> Effects, StuffType StuffType);
	Shell(int Rarity, std::string Data, StuffType StuffType);

	int getNumberEffect() const					{ return (int)effects.size(); }
	std::vector<ShellEffect> getEffects() const	{ return effects; }
	std::string getData() const					{ return data; }
	int getRarity() const						{ return rarity; }

private:
	std::vector<ShellEffect> effects;
	int rarity;
	std::string data;
	StuffType stuffType;
};

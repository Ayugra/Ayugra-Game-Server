#pragma once
#include <string>
#include <vector>
#include "Game/Accounts/Character/Attributes/Inventory/EnhancementEffect.h"

// Need to implement bcard system before going further in this class.
class Enhancement
{
public:
	Enhancement() : data(), numberOptions(0), numberUpgrade(0), broken(true) {}
	Enhancement(std::string Data, bool Broken);

	std::string getData() const		{ return data; }
	int getNumberUpgrade() const	{ return numberUpgrade; }
	size_t getNumberOptions() const { return numberOptions; }
	bool isBroken() const			{ return broken; }

private:
	bool broken;
	std::string data;
	int numberUpgrade;
	size_t numberOptions;
};

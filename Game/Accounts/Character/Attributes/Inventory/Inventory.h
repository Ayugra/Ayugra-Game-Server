#pragma once
#include "Game/Accounts/Character/Attributes/Inventory/SubInventory.h"
#include "Game/Accounts/Character/Attributes/Inventory/WornStuff.h"
#include "Game/Types/InventoryType.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void loadInventory(int characterId);
	SubInventory getSubInventory(InventoryType invType);
	std::map<InventoryType, SubInventory> getSubInventories() { return subInventories; }
	//void setExtension(int extension);
	int getGold() const { return gold; }
	int getBankGold() const { return bankGold; }
	WornStuff getWornStuff() const { return wornStuff; }

private:
	std::map<InventoryType, SubInventory> subInventories;
	WornStuff wornStuff;
	int additionalSlotUnlocked;
	int gold;
	int bankGold;
};

#pragma once
#include <vector>
#include <string>
#include "Game/Types/InventoryType.h"
#include "Game/Accounts/Character/Attributes/Inventory/Shell.h"
#include "Game/Accounts/Character/Attributes/Inventory/Enhancement.h"

class Item
{
public:
	Item() : vnum(-1) {} // itemid characid invtype slot itemid vnum qtity rarity up perf acti enha
	Item(int ItemId, int OwnerId, InventoryType InvType, int Slot, int Vnum, int Quantity,
		int Rarity, int Upgrade, int Perfection, bool Activated, Enhancement Enhancement, Shell Shell);
	~Item();

	InventoryType getInventoryType() const { return invType; }
	int getItemId() const { return itemId; }
	int getOwnerId() const { return ownerId; }
	int getSlot() const { return slot; }
	int getVnum() const { return vnum; }
	int getQuantity() const { return quantity; }
	int getRarity() const { return rarity; } // TODO WITH ENUM
	int getUpgrade() const { return upgrade; }
	bool isActivated() const { return activated; }
	Enhancement getEnhancement() const { return enhancement; }
	Shell getShell() const { return shell; }
	int getColor() const { return 0; } // TODO
	int getPerfection() const { return perfection; }

	static Item createItem(std::vector<std::string> data);
	static Item createWornItem(std::vector<std::string> data, int OwnerId, bool IsSp);

private:
	InventoryType invType;
	int itemId;
	int ownerId;
	int slot; // Keep it synchronized
	int vnum;
	int quantity;
	bool activated;

	int rarity;
	int upgrade;
	int perfection;
	Enhancement enhancement; // make class
	Shell shell; // make class
};

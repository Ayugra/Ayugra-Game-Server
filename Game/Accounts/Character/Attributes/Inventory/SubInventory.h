#pragma once
#include <map>
#include "Game/Accounts/Character/Attributes/Inventory/Item.h"

class SubInventory
{
public:
	SubInventory() : extension(0) {}
	SubInventory(int Extension);
	~SubInventory();

	void addItem(int slot, Item item);

	std::vector<Item> getItems();
	std::map<int, Item> getMappedItems();
	Item getItem(int slot);


private:
	std::map<int, Item> items;
	int extension;
};

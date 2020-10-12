#pragma once
#include <map>
#include "Game/Accounts/Character/Attributes/Inventory/Item.h"

class WornStuff
{
public:
	WornStuff()
	{

	}

	~WornStuff()
	{

	}

	std::vector<Item> getItems();
	std::map<int, Item> getMappedItems();
	Item getItem(int slot);
	void remove(int type);

	void addItem(int type, Item item);

private:
	std::map<int, Item> items; // enum instead of int ?
};

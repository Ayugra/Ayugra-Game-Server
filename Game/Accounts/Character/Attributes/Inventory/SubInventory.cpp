#include "SubInventory.h"

SubInventory::SubInventory(int Extension)
	: extension(Extension)
{
}

SubInventory::~SubInventory()
{
}

void SubInventory::addItem(int slot, Item item)
{
	items.insert({ slot, item });
}

std::vector<Item> SubInventory::getItems()
{
	std::vector<Item> itms;
	for (auto&& i : items)
		itms.push_back(i.second);
	return itms;
}

std::map<int, Item> SubInventory::getMappedItems()
{
	return items;
}

Item SubInventory::getItem(int slot)
{
	if (items.find(slot) != items.end())
		return Item();
	return items.at(slot);
}

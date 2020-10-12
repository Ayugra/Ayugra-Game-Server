#include "WornStuff.h"

std::vector<Item> WornStuff::getItems()
{
	std::vector<Item> itms;
	for (auto&& i : items)
		itms.push_back(i.second);
	return itms;
}

std::map<int, Item> WornStuff::getMappedItems()
{
	return items;
}

Item WornStuff::getItem(int type)
{
	if (items.find(type) == items.end())
		return Item();
	return items.at(type);
}

void WornStuff::remove(int type)
{
	if (items.find(type) != items.end())
		items.erase(type);
}

void WornStuff::addItem(int type, Item item)
{
	remove(type);
	items.insert({ type, item });
}

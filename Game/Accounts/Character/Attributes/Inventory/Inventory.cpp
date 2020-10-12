#include "Inventory.h"
#include "Utils.h"
#include "Database/DatabaseManager.h"
#include <iostream>

Inventory::Inventory()
	: gold(0)
	, bankGold(0)
	, additionalSlotUnlocked(0)
{
	subInventories.insert({ InventoryType::EQUIPMENT, SubInventory() });
	subInventories.insert({ InventoryType::MAIN, SubInventory() });
	subInventories.insert({ InventoryType::ETC, SubInventory() });
	subInventories.insert({ InventoryType::MINILAND, SubInventory() });
	subInventories.insert({ InventoryType::COSTUMES, SubInventory() });
	subInventories.insert({ InventoryType::SP, SubInventory() });
}

Inventory::~Inventory()
{
}

void Inventory::loadInventory(int characterId)
{
	std::vector<std::vector<std::string>> res = DatabaseManager::call("p_get_inventory", { SQL_TYPE::INT, std::to_string(characterId) });
	for (size_t i = 0; i < res.size(); i++)
	{
		Item item = Item::createItem(res[i]);
		if (item.getVnum() == -1)
			continue;
		subInventories.at(item.getInventoryType()).addItem(item.getSlot(), item);
	}

	res = DatabaseManager::call("p_get_character_gold", { SQL_TYPE::INT, std::to_string(characterId) });
	if (!res.empty() && res[0].size() == 2)
	{
		gold = ToNumber<int>(res[0][0].c_str());
		bankGold = ToNumber<int>(res[0][1].c_str());
	}

	res = DatabaseManager::call("p_get_character_worn_equipment", { SQL_TYPE::INT, std::to_string(characterId) });
	if (!res.empty())
	{
		for (size_t i = 0; i < res.size(); i++)
		{
			Item item = Item::createWornItem(res[i], characterId, i == 12);
			if (item.getVnum() == -1)
				continue;
			wornStuff.addItem((int)i, item);
		}
	}
}

SubInventory Inventory::getSubInventory(InventoryType invType)
{
	return SubInventory();
}

//void Inventory::setExtension(int extension)
//{
	// ? additionalSlotUnlocked += extension;
	/*
	Erenia : +8
Aventurier : +4
Sac à dos : +12
Ticket ext : +60
	*/
//}

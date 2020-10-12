#include "Item.h"
#include "Utils.h"
#include "Configuration/GameFiles/ItemDatParser.h"

Item::Item(int ItemId, int OwnerId, InventoryType InvType, int Slot, int Vnum, int Quantity,
	int Rarity, int Upgrade, int Perfection, bool Activated, Enhancement Enhancement, Shell Shell)
	: invType(InvType)
	, itemId(ItemId)
	, ownerId(OwnerId)
	, slot(Slot)
	, vnum(Vnum)
	, quantity(Quantity)
	, activated(Activated)
	, rarity(Rarity)
	, upgrade(Upgrade)
	, perfection(Perfection)
	, enhancement(Enhancement)
	, shell(Shell)
{
}

Item::~Item()
{
}

Item Item::createItem(std::vector<std::string> data)
{
	if (data.size() != 13)
		return Item();
	ItemStruct itm = ItemDat::getItemStruct(ToNumber<int>(data[5].c_str()));
	return Item
	(
		ToNumber<int>(data[0].c_str()),								// ItemId
		ToNumber<int>(data[1].c_str()),								// OwnerId
		static_cast<InventoryType>(ToNumber<int>(data[2].c_str())),	// InventoryType
		ToNumber<int>(data[3].c_str()),								// Slot
																	// TOFIX: ItemId duplicate
		ToNumber<int>(data[5].c_str()),								// Vnum
		ToNumber<int>(data[6].c_str()),								// Quantity
		ToNumber<int>(data[7].c_str()),								// Rarity
		ToNumber<int>(data[8].c_str()),								// Upgrade
		ToNumber<int>(data[9].c_str()),								// Perfection
		ToNumber<int>(data[10].c_str()),							// Activated
		Enhancement(data[11], false /*TODO : broken*/),				// Enhancement
		Shell(0 /*TODO : rarity*/,data[12], itm.isArmor() ? StuffType::ARMOR : StuffType::WEAPON)	// Shell
	);
}

Item Item::createWornItem(std::vector<std::string> data, int OwnerId, bool IsSp)
{
	if (data.size() != 7)
		return Item();
	ItemStruct itm = ItemDat::getItemStruct(ToNumber<int>(data[1].c_str())); // Possible refactorisation
	return Item
	(
		ToNumber<int>(data[0].c_str()),								// ItemId
		OwnerId,													// OwnerId
		IsSp ? InventoryType::SP : InventoryType::EQUIPMENT,		// InventoryType
		-1,															// Slot
		ToNumber<int>(data[1].c_str()), 							// Vnum
		1, 															// Quantity
		ToNumber<int>(data[2].c_str()), 							// Rarity
		ToNumber<int>(data[3].c_str()), 							// Upgrade
		ToNumber<int>(data[4].c_str()), 							// Perfection
		false, 														// Activated
		Enhancement(data[5], false /*TODO : broken*/),				// Enhancement
		Shell(0 /*TODO : rarity*/, data[6], itm.isArmor() ? StuffType::ARMOR : StuffType::WEAPON)	// Shell
	);
}

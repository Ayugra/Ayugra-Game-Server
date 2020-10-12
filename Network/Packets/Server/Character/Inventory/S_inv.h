#pragma once
#include <vector>
#include "Network/Packets/BaseServerPacket.h"
#include "Game/Accounts/Character/Attributes/Inventory/Item.h"
#include "Game/Types/InventoryType.h"                                             

class S_inv : public BaseServerPacket
{
public:
    S_inv(InventoryType invType, std::vector<Item> item)
        : BaseServerPacket("inv")
    {
        packet += " " + std::to_string(static_cast<int>(invType));
        if (invType == InventoryType::EQUIPMENT)
        {
            for (size_t i = 0; i < item.size(); i++)
            { // inv 0 : slot.vnum.rarity.upgrade.activated.enhancement
                packet += " " + std::to_string(item[i].getSlot());
                packet += "." + std::to_string(item[i].getVnum());
                packet += "." + std::to_string(item[i].getRarity());
                packet += "." + std::to_string(item[i].getUpgrade());
                packet += "." + std::to_string(item[i].isActivated());
                packet += "." + std::to_string(item[i].getEnhancement().getNumberUpgrade());
            }
        }
        else if (invType == InventoryType::MAIN)
        {
            for (size_t i = 0; i < item.size(); i++)
            { // inv 1 : slot.vnum.quantity
                packet += " " + std::to_string(item[i].getSlot());
                packet += "." + std::to_string(item[i].getVnum());
                packet += "." + std::to_string(item[i].getQuantity());
            }
        }
        else if (invType == InventoryType::ETC)
        {
            for (size_t i = 0; i < item.size(); i++)
            { // inv 1 : slot.vnum.quantity
                packet += " " + std::to_string(item[i].getSlot());
                packet += "." + std::to_string(item[i].getVnum());
                packet += "." + std::to_string(item[i].getQuantity());
            }
        }
        else if (invType == InventoryType::SP)
        {
            for (size_t i = 0; i < item.size(); i++)
            { // inv 6 : slot.vnum.?.wingUpgrade.stoneUpgrade
                packet += " " + std::to_string(item[i].getSlot());
                packet += "." + std::to_string(item[i].getVnum());
                packet += ".0"; // ?
                packet += "." + std::to_string(item[i].getUpgrade());
                packet += "." + std::to_string(item[i].getPerfection());
            }
        }
        else if (invType == InventoryType::COSTUMES)
        {
            for (size_t i = 0; i < item.size(); i++)
            { // inv 7 : slot.vnum.?.coloration.?
                packet += " " + std::to_string(item[i].getSlot());
                packet += "." + std::to_string(item[i].getVnum());
                packet += ".0"; // ?
                packet += "." + std::to_string(item[i].getColor());
                packet += ".0"; // ?
            }
        }
    }
};

#pragma once
#include <map>
#include "Network/Packets/BaseServerPacket.h"
#include "Game/Accounts/Character/Attributes/Inventory/Item.h"

class S_equip : public BaseServerPacket
{
public:
    S_equip(std::map<int, Item> items)
        : BaseServerPacket("equip")
    {
        if (items.size() == 17)
        {
            packet += " " + std::to_string(items[0].getUpgrade() * 10 + items[0].getRarity());
            packet += " " + std::to_string(items[1].getUpgrade() * 10 + items[1].getRarity());

            for (auto& itm : items)
            {
                packet += " " + std::to_string(itm.first);
                packet += "." + std::to_string(itm.second.getVnum());
                packet += "." + std::to_string(itm.second.getRarity());
                packet += "." + std::to_string(itm.second.getUpgrade());
                packet += "." + std::to_string(itm.second.getPerfection());
                packet += "." + std::to_string(itm.second.getEnhancement().getNumberUpgrade());
            }
        }
    }
};

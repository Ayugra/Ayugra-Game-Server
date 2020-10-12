#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Configuration/GameFiles/ItemDatParser.h"
#include "Game/Accounts/Character/OwnCharacter.h"
#include "Game/Types/EntityType.h"
#include "Game/Types/WingType.h"

class S_c_mode : public BaseServerPacket
{
public:
    S_c_mode(EntityType entityType, int entityId, int morphId, int morphUpgrade, WingType wingType, bool isArenaWinner, int size, int wingItemMorphId)
        : BaseServerPacket("c_mode")
    {
        packet += " " + std::to_string(static_cast<int>(entityType));
        packet += " " + std::to_string(entityId);
        packet += " " + std::to_string(morphId);
        packet += " " + std::to_string(morphUpgrade);
        packet += " " + std::to_string(static_cast<int>(wingType));
        packet += " " + std::to_string(isArenaWinner);
        packet += " " + std::to_string(size);
        packet += " " + std::to_string(wingItemMorphId);
    }

    S_c_mode(const OwnCharacter& character)
        : BaseServerPacket("c_mode")
    {
        packet += " " + std::to_string(static_cast<int>(EntityType::PLAYER));
        packet += " " + std::to_string(character.getId());
        packet += " " + std::to_string(0); // TODO : MorphId
        packet += " " + std::to_string(0); // TODO : SP Upgrade
        packet += " " + std::to_string(static_cast<int>(WingType::NONE));
        packet += " " + std::to_string(1); // TODO : IsArenaWinner
        packet += " " + std::to_string(15); // TODO : Size

        // POSSIBLE CRASH IF ITEM DOESN'T EXIST ??
        ItemStruct itm = ItemDat::getItemStruct(character.getInventory().getWornStuff().getItem(16).getVnum());
        packet += " " + std::to_string(itm.getItemMorphId());
    }
};

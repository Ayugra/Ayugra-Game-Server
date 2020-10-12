#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Configuration/GameFiles/ItemDatParser.h"
#include "Game/Accounts/Character/OwnCharacter.h"

class S_c_info : public BaseServerPacket
{
public:
    S_c_info(std::string pseudonym, int groupId, int familyId, int familyRole, int characterId, int authority, GenderType gender,
        HairStyleType hStyle, int hColor, ClassType charClass, ReputationType reputationIcon, int compliment, int morphId, bool isInvisible,
        int familyLevel, int spUpgrade, bool isArenaWinner, int wingsId)
        : BaseServerPacket("c_info")
    {
        packet += " " + pseudonym;
        packet += " - " + std::to_string(groupId);
        packet += " " + std::to_string(familyId);
        packet += "." + std::to_string(familyRole);
        packet += " " + std::to_string(characterId);
        packet += " " + std::to_string(authority);
        packet += " " + std::to_string(static_cast<int>(gender));
        packet += " " + std::to_string(static_cast<int>(hStyle));
        packet += " " + std::to_string(hColor);
        packet += " " + std::to_string(static_cast<int>(charClass));
        packet += " " + std::to_string(static_cast<int>(reputationIcon));
        packet += " " + std::to_string(compliment);
        packet += " " + std::to_string(morphId);
        packet += " " + std::to_string(isInvisible);
        packet += " " + std::to_string(familyLevel);
        packet += " " + std::to_string(spUpgrade);
        packet += " " + std::to_string(isArenaWinner);
        packet += " " + std::to_string(wingsId);
    }

    S_c_info(const OwnCharacter& character)
        : BaseServerPacket("c_info")
    {
        packet += " " + character.getPseudonym();
        packet += " - " + std::to_string(-1); // TODO : group id
        packet += " " + std::to_string(-1); // TODO : familly id
        packet += "." + std::to_string(-1); // TODO : familly role conststring
        packet += " -"; // TODO : familly name
        packet += " " + std::to_string(character.getId());
        packet += " " + std::to_string(character.getAuthority());
        packet += " " + std::to_string(static_cast<int>(character.getGender()));
        packet += " " + std::to_string(static_cast<int>(character.getHairStyle()));
        packet += " " + std::to_string(character.getHairColor());
        packet += " " + std::to_string(static_cast<int>(character.getClass()));
        packet += " " + std::to_string(static_cast<int>(character.getReputationProperties().reputationIcon));
        packet += " " + std::to_string(character.getReputationProperties().compliment);
        packet += " " + std::to_string(0); // TODO : MorphID
        packet += " " + std::to_string(0); // TODO : IsInvisible
        packet += " " + std::to_string(0); // TODO : familly level
        packet += " " + std::to_string(0); // TODO : sp upgrade
        packet += " " + std::to_string(1); // TODO : isArenaWinner

        // POSSIBLE CRASH IF ITEM DOESN'T EXIST ??
        ItemStruct itm = ItemDat::getItemStruct(character.getInventory().getWornStuff().getItem(16).getVnum());
        packet += " " + std::to_string(itm.getItemMorphId());
    }
};

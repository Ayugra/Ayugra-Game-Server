#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Game/Types/GenderType.h"
#include "Game/Types/HairStyleType.h"
#include "Game/Types/ClassType.h"
#include "Game/Types/ReputationType.h"                                             

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
};

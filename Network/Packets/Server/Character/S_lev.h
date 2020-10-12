#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Game/Accounts/Character/OwnCharacter.h"
#include "Configuration/XpConfiguration.h"

class S_lev : public BaseServerPacket
{
public:
    S_lev(int levelN, int xpN, int levelJ, int xpJ, int upN, int upJ, int reputation, int cp, int xpH, int levelH, int upH)
        : BaseServerPacket("lev")
    {
        packet += " " + std::to_string(levelN);
        packet += " " + std::to_string(xpN);
        packet += " " + std::to_string(levelJ);
        packet += " " + std::to_string(xpJ);
        packet += " " + std::to_string(upN);
        packet += " " + std::to_string(upJ);
        packet += " " + std::to_string(reputation);
        packet += " " + std::to_string(cp);
        packet += " " + std::to_string(xpH);
        packet += " " + std::to_string(levelH);
        packet += " " + std::to_string(upH);
    }

    S_lev(const OwnCharacter& character)
        : BaseServerPacket("lev")
    {
        packet += " " + std::to_string(character.getLevelProperties().levelN);
        packet += " " + std::to_string(character.getLevelProperties().xpN);
        packet += " " + std::to_string(character.getLevelProperties().levelJ);
        packet += " " + std::to_string(character.getLevelProperties().xpJ);
        packet += " " + std::to_string(XpConfiguration::getXpNeeded(XpType::NORMAL, character.getLevelProperties().levelN));
        packet += " " + std::to_string(XpConfiguration::getXpNeeded(XpType::JOB, character.getLevelProperties().levelJ));
        packet += " " + std::to_string(character.getReputationProperties().reputationAmount);
        packet += " " + std::to_string(0); // TODO : CP
        packet += " " + std::to_string(character.getLevelProperties().xpH);
        packet += " " + std::to_string(character.getLevelProperties().levelH);
        packet += " " + std::to_string(XpConfiguration::getXpNeeded(XpType::HERO, character.getLevelProperties().levelH));
    }
};

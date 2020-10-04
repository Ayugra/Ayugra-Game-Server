#pragma once

#include "Network/Packets/BaseServerPacket.h"

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
};

#pragma once

#include "Network/Packets/BaseServerPacket.h"                                        

class S_gold : public BaseServerPacket
{
public:
    S_gold(int gold, int bankGold)
        : BaseServerPacket("gold")
    {
        packet += " " + std::to_string(gold);
        packet += " " + std::to_string(bankGold);
    }
};

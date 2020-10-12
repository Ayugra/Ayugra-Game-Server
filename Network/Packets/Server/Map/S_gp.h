#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Game/Entities/Portal.h"

class S_gp : public BaseServerPacket
{
public:
    S_gp(Portal portal)
        : BaseServerPacket("gp")
    {
        packet += " " + std::to_string(portal.getX());
        packet += " " + std::to_string(portal.getY());
        packet += " " + std::to_string(portal.getDestMapId());
        packet += " " + std::to_string(static_cast<int>(portal.getPortalType()));
        packet += " " + std::to_string(portal.getEntityID());
        packet += " " + std::to_string(portal.isInvisible());
    }

};

/*
    PacketGp(QStringList Packet);
short getX();
short getY();
int getMapID();
PortalType getType();
int getID();
bool isInvisible();
*/
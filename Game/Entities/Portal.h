#pragma once
#include "Game/Entities/BaseEntity.h"
#include "Game/Types/PortalType.h"

class Portal : public BaseEntity
{
public:
	Portal(int id, int MapId, int x, int y, int DestMapId, int DestMapX, int DestMapY, bool Closed, bool Invisible, PortalType Type)
		: BaseEntity(EntityType::MAP, id, x, y)
		, mapId(MapId)
		, destMapId(DestMapId)
		, destMapX(DestMapX)
		, destMapY(DestMapY)
		, type(Type)
		, invisible(Invisible)
		, closed(Closed)
	{

	}

	int getDestMapId() const { return destMapId; }
	int getDestMapX() const { return destMapX; }
	int getDestMapY() const { return destMapY; }
	bool isClosed() const { return closed; }
	bool isInvisible() const { return invisible; }
	PortalType getPortalType() const { return type; }

private:
	int mapId;
	int destMapId;
	int destMapX;
	int destMapY;
	bool closed;
	bool invisible;
	PortalType type;
};

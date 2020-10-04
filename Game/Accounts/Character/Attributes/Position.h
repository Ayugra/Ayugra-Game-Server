#pragma once

class Position
{
public:
	Position()
		: mapId(-1)
		, posX(-1)
		, posY(-1)
		, direction(-1)
	{}
	Position(int MapId, int PosX, int PosY)
		: mapId(MapId)
		, posX(PosX)
		, posY(PosY)
		, direction(2)
	{}
	int mapId;
	int posX;
	int posY;
	int direction;
};
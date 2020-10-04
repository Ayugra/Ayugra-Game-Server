#pragma once

class Level
{
public:
	Level()
		: levelN(-1)
		, levelJ(-1)
		, levelH(-1)
		, xpN(-1)
		, xpJ(-1)
		, xpH(-1)
	{}
	Level(int LevelN, int LevelJ, int LevelH, int XpN, int XpJ, int XpH)
		: levelN(LevelN)
		, levelJ(LevelJ)
		, levelH(LevelH)
		, xpN(XpN)
		, xpJ(XpJ)
		, xpH(XpH)
	{}

	int levelN;
	int levelJ;
	int levelH;
	int xpN;
	int xpJ;
	int xpH;
};
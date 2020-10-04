#pragma once
#include "Game/UIManager/Ladder/ReputationManager.h"
#include "Game/Types/DignityType.h"
#include "Database/DatabaseManager.h"

class Reputation
{
public:
	Reputation()
		: reputationAmount(0)
		, reputationIcon(ReputationType::BEGINNER_1)
		, dignityAmount(0)
		, dignityIcon(DignityType::BASIC)
		, compliment(0)
	{}
	Reputation(int ReputationAmount, ReputationType ReputationIcon, int DignityAmount, DignityType DignityIcon, int Compliment)
		: reputationAmount(ReputationAmount)
		, reputationIcon(ReputationIcon)
		, dignityAmount(DignityAmount)
		, dignityIcon(DignityIcon)
		, compliment(Compliment)
	{}

	int reputationAmount;
	ReputationType reputationIcon;
	int dignityAmount;
	DignityType dignityIcon;
	int compliment;
};
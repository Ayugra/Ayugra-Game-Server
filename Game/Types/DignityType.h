#pragma once

enum class DignityType
{
	BASIC = 1,			// Don't show dignity (default)
	SUSPECTED = 2,		// -100 ~ -200
	NAME_ONLY = 3,		// -201 ~ -400
	NOT_QUALIFIED = 4,	// -401 ~ -600
	USELESS = 5,		// -601 ~ 800
	STUPID = 6			// -801 ~ 1000
};

static DignityType getDignityType(int dignityAmount)
{
	if (dignityAmount > -100)
		return DignityType::BASIC;
	else if (dignityAmount >= -200)
		return DignityType::SUSPECTED;
	else if (dignityAmount >= -400)
		return DignityType::NAME_ONLY;
	else if (dignityAmount >= -600)
		return DignityType::NOT_QUALIFIED;
	else if (dignityAmount >= -800)
		return DignityType::USELESS;
	return DignityType::STUPID;
}
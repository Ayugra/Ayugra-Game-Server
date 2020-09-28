#pragma once

#include <string>


const std::string ALLOWED_CHAR_USERNAME = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

/* Return :
0 : fine
1 : not in bound
2 : forbidden character
*/
static int isPseudonymAllowed(const std::string& pseudonym)
{
	if (pseudonym.size() < 4 || pseudonym.size() > 14)
		return 1;
	for (size_t i = 0; i < pseudonym.size(); i++)
	{
		char c = pseudonym[i];
		if (!(c >= 0x23 && c <= 0x26) &&
			!(c >= 0x28 && c <= 0x2E) &&
			!(c >= 0x30 && c <= 0x39) &&
			!(c >= 0x3C && c <= 0x5A) &&
			!(c >= 0x5E && c <= 0x7E))
			return 2;
	}
	return 0;
}

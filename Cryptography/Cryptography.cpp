#include "Cryptography.h"
#include <algorithm>
#include <math.h>

const char* Cryptography::ENCRYPTION_TABLE = "\x00\x20\x2D\x2E\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x0A\x00";
const char* Cryptography::DECRYPTION_TABLE = "\x00\x20\x2D\x2E\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\xFF\x00";
const size_t Cryptography::TABLE_SIZE = 16;

std::string Cryptography::WorldEncrypt(std::string packet)
{
	return pack(packet, ENCRYPTION_TABLE);
}

std::string Cryptography::WorldDecrypt(std::string *packet, int encryptionKey, bool isFirstPacket)
{
	if(!packet)
		return "";
	std::string output;
	int stype = (-1) * (isFirstPacket) + (stype = (encryptionKey >> 6) & 3) * (!isFirstPacket);
	unsigned char key = encryptionKey & 0xFF;
	unsigned char c = 0;
	bool found = false;
	for(auto&& i : *packet)
	{
		if (stype == 0)
			c = ((i - key - 0x40) & 0xFF);
		else if (stype == 1)
			c = ((i + key + 0x40) & 0xFF);
		else if (stype == 2)
			c = (((i - key - 0x40) ^ 0xC3) & 0xFF);
		else if (stype == 3)
			c = (((i + key + 0x40) ^ 0xC3) & 0xFF);
		else
			c = ((i - 0xF) & 0xFF);
		output.push_back(c);
		if (c == 0xFF)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		packet->erase(0, output.size());
		return unpack(output, DECRYPTION_TABLE);
	}
	return "";
}

std::vector<bool> Cryptography::getMask(std::string packet, const char* charset)
{
	std::vector<bool> output;
	for (auto&& c : packet)
	{
		bool found = false;
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (charset[j] == c)
			{
				found = true;
				break;
			}
		}
		output.push_back(found);
	}
	return output;
}

size_t Cryptography::calculateMaskLength(size_t start, std::vector<bool> mask, bool value)
{
	size_t currentLength = 0;
	for (; start < mask.size(); start++)
	{
		if (mask[start] == value)
			currentLength++;
		else
			break;
	}
	return currentLength;
}

std::string Cryptography::pack(std::string packet, const char* charsToPack)
{
	std::string output;
	std::vector<bool> mask = getMask(packet, charsToPack);
	size_t pos = 0;
	while (mask.size() > pos)
	{
		size_t currentChunkLength = calculateMaskLength(pos, mask, false);
		for (size_t i = 0; i < currentChunkLength; i++)
		{
			if (pos > mask.size())
				break;
			if (i % 0x7E == 0)
				output.push_back(std::min(currentChunkLength - i, (size_t)0x7E));
			output.push_back((unsigned char)packet[pos] ^ 0xFF);
			pos++;
		}

		currentChunkLength = calculateMaskLength(pos, mask, true);
		for (size_t i = 0; i < currentChunkLength; i++)
		{
			if (pos > mask.size())
				break;
			if (i % 0x7E == 0)
				output.push_back(std::min(currentChunkLength - i, (size_t)0x7E) | 0x80);

			unsigned char currentValue = 0;
			for (int i = 0; i < TABLE_SIZE; i++)
			{
				if (charsToPack[i] == packet[pos])
				{
					currentValue = i;
					break;
				}
			}

			if (i % 2 == 0)
				output.push_back(((unsigned char)currentValue << 4));
			else
				output[output.size() - 1] |= currentValue;

			pos++;
		}
	}
	output.push_back(0xFF);
	return output;
}

std::string Cryptography::unpack(std::string packet, const char* charsToUnpack)
{
	std::string output;

	for (size_t pos = 0; packet.size() > pos && (unsigned char)packet[pos] != 0xFF;)
	{
		unsigned char currentChunkLength = (unsigned char)packet[pos] & 0x7F;
		bool isPacked = (unsigned char)packet[pos] & 0x80;
		pos++;
		if (isPacked)
		{
			for (size_t i = 0; i < ceil((double)currentChunkLength / 2) && pos < packet.size(); i++)
			{
				unsigned char twoChars = packet[pos];
				pos++;
				unsigned char leftChar = twoChars >> 4;
				output.push_back(charsToUnpack[leftChar]);
				unsigned char rightChar = twoChars & 0xF;
				if (rightChar == 0)
					break;
				output.push_back(charsToUnpack[rightChar]);
			}
		}
		else
		{
			for (size_t i = 0; i < currentChunkLength && pos < packet.size(); i++, pos++)
				output.push_back(((unsigned char)packet[pos] ^ 0xFF));
		}
	}
	return output;
}
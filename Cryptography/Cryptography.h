#pragma once

#include <string>
#include <vector>
#include <iostream>

class Cryptography
{
public:
    static std::string WorldEncrypt(std::string packet);
    static std::string WorldDecrypt(std::string *packet, int encryptionKey, bool isFirstPacket);

private:
    static std::vector<bool> getMask(std::string packet, const char* charset);
    static size_t calculateMaskLength(size_t start, std::vector<bool> mask, bool value);
    static std::string pack(std::string packet, const char* charsToPack);
    static std::string unpack(std::string packet, const char* charsToUnpack);

    static const char* ENCRYPTION_TABLE;
    static const char* DECRYPTION_TABLE;
    static const size_t TABLE_SIZE;
};

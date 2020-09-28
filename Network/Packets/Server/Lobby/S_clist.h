#pragma once

#include "Network/Packets/BaseServerPacket.h"
#include "Game/Accounts/LobbyCharacters/LobbyCharacter.h"

class S_clist : public BaseServerPacket
{
public:
	S_clist(LobbyCharacter lobC)
		: BaseServerPacket("clist")
	{
		packet += " " + lobC.getLobbyPacket();
	}
};
#include "Client.h"
#include "Configuration/XpConfiguration.h"
#include "Game/UIManager/Ladder/ReputationManager.h"
#include "Game/UIManager/Ladder/Act4PointsManager.h"
#include "Game/UIManager/Ladder/ComplimentManager.h"
#include "Packets/Server/Messages/S_tit.h"
#include "Packets/Server/Character/S_fd.h"
#include "Packets/Server/UI/Ladder/S_flinit.h"
#include "Packets/Server/UI/Ladder/S_kdlinit.h"
#include "Packets/Server/UI/Ladder/S_clinit.h"
#include "Packets/Server/Character/S_c_info.h"
#include "Packets/Server/Map/S_at.h"
#include "Packets/Server/Map/S_c_map.h"
#include "Packets/Server/Character/S_c_info_reset.h"
#include "Packets/Server/Character/S_lev.h"
#include "Packets/Server/Character/Inventory/S_inv.h"
#include "Packets/Server/Character/Inventory/S_gold.h"
#include "Packets/Server/Character/Inventory/S_equip.h"
#include "Packets/Server/Character/Inventory/S_e_info.h"
#include <iostream>

Client::Client(std::function<void(std::string)> CbSendPacket, std::function<void()> CbDisconnect)
	: cbSendPacket(CbSendPacket)
	, cbDisconnect(CbDisconnect)
	, account(CbDisconnect)
	, connectionId(-1)
{

}

Client::~Client()
{

}

void Client::setEncryptionKey(int EncryptionKey)
{
	account.setEncryptionKey(EncryptionKey);
}

void Client::setConnectionId(int ConnectionId)
{
	connectionId = ConnectionId;
	account.setConnectionId(ConnectionId);
}

int Client::getConnectionId() const
{
	return connectionId;
}

int Client::getAccountId() const
{
	return account.getAccountId();
}

OwnCharacter Client::getConnectedCharacter() const
{
	return *character;
}

void Client::dispatchPacket(const BaseClientPacket& Packet)
{

	// Handle all this code in a thread pool
	std::vector<std::string> response;

	if (!account.isConnected())
	{
		response = account.handlePacket(Packet);
		if (!response.empty())
		{
			sendPacket(response);
		}
		return;// Special for those packets : no more actions can be done
	}
	response = handlePacket(Packet);
	if (!response.empty())
		sendPacket(response);
	response = cbRetrieveCharacter(character, Packet);
	if (!response.empty())
		sendPacket(response);
}

void Client::setRetrieveCharacterCallback(std::function<std::vector<std::string>(std::shared_ptr<OwnCharacter>, const BaseClientPacket&)> CbRetrieveCharacter)
{
	cbRetrieveCharacter = CbRetrieveCharacter;
}

void Client::sendPacket(std::vector<std::string> response)
{
	if(response.empty())
		return;
	for (auto&& resp : response)
		cbSendPacket(resp);
}

std::vector<std::string> Client::handlePacket(const BaseClientPacket& Packet)
{
	std::vector<std::string> response;
	if (Packet.getHeader() == "game_start")
		response = handle_game_start(Packet);
	else if (Packet.getHeader() == "eqinfo")
		response = handle_eqinfo(Packet);
	return response;
}

std::vector<std::string> Client::handle_game_start(const R_game_start& Packet)
{
	if (character != nullptr)
	{
		cbDisconnect();
		return {};
	}
	std::vector<std::string> response;
	character = std::make_shared<OwnCharacter>(account.getSelectedLobbyCharacter(), cbSendPacket);
	response.push_back(S_tit(static_cast<int>(character->getClass()) + 35, character->getPseudonym()).getPacketString());
	response.push_back(S_fd(character->getReputationProperties().reputationAmount, character->getReputationProperties().reputationIcon
		, character->getReputationProperties().dignityAmount, character->getReputationProperties().dignityIcon).getPacketString());
	response.push_back(S_c_info_reset().getPacketString());
	response.push_back(S_flinit(ReputationManager::getReputationLadderEntities()).getPacketString());
	response.push_back(S_kdlinit(Act4PointsManager::getAct4pointsLadderEntities()).getPacketString());
	response.push_back(S_clinit(ComplimentManager::getComplimentLadderEntities()).getPacketString());
	std::map<InventoryType, SubInventory> subInv = character->getInventory().getSubInventories();
	for (auto inv : subInv)
		response.push_back(S_inv(inv.first, inv.second.getItems()).getPacketString());
	response.push_back(S_gold(character->getInventory().getGold(), character->getInventory().getBankGold()).getPacketString());

	return response;
}

std::vector<std::string> Client::handle_eqinfo(const R_eqinfo& Packet)
{
	if (!Packet.isValid())
		return {};
	if (Packet.getInventorySlot() == 0)
		return { S_e_info(character->getInventory().getWornStuff().getItem(Packet.getSlot())).getPacketString() };
	else if (Packet.getInventorySlot() == 1)
	{

	}
	return {};
}

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
	return character;
}

void Client::dispatchPacket(const BaseClientPacket& Packet)
{

	// Handle all this code in a thread pool


	std::vector<std::string> response;
	response = account.handlePacket(Packet);
	if (!response.empty())
	{
		sendPacket(response);
		return;// Special for those packets : no more actions can be done
	}
	response = handlePacket(Packet);
	if (!response.empty())
		sendPacket(response);


}

void Client::setRetrieveCharacterCallback(std::function<void(std::shared_ptr<OwnCharacter>)> CbRetrieveCharacter)
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
	{
		response = handle_game_start(Packet);
	}
	return response;
}

std::vector<std::string> Client::handle_game_start(const R_game_start& Packet)
{
	if (character.getId() != -1)
	{
		cbDisconnect();
		return {};
	}
	std::vector<std::string> response;
	character = OwnCharacter(account.getSelectedLobbyCharacter());
	response.push_back(S_tit(static_cast<int>(character.getClass()) + 35, character.getPseudonym()).getPacketString());
	response.push_back(S_fd(character.getReputationProperties().reputationAmount, character.getReputationProperties().reputationIcon
		, character.getReputationProperties().dignityAmount, character.getReputationProperties().dignityIcon).getPacketString());
	//response.push_back(S_c_info(character.getPseudonym(), -1, -1, -1, character.getId(), account.getAuthority(), character.getGender(),
	//	character.getHairStyle(), character.getHairColor(), character.getClass(), character.getReputationProperties().reputationIcon,
	//	character.getReputationProperties().compliment, character.getMorphId(), character.isInvisible(), character.getFamilyLevel(),
	//	character.getSpUpgrade(), character.isArenaWinner(), character.getWingsId()));
	response.push_back("c_info " + character.getPseudonym() + " - -1 -1 - " + std::to_string(character.getId()) + " 1 0 1 0 9 0 1 0 0 0 0 0 0 0");
	response.push_back(S_c_info_reset().getPacketString());
	response.push_back(S_at(character.getId(), character.getPositionProperties().mapId, character.getPositionProperties().posX,
		character.getPositionProperties().posY, character.getPositionProperties().direction, 0, 0, 1, -1).getPacketString()); // TODO : music and unk
	response.push_back(S_c_map(0, character.getPositionProperties().mapId, true).getPacketString());
	response.push_back(S_flinit(ReputationManager::getReputationLadderEntities()).getPacketString());
	response.push_back(S_kdlinit(Act4PointsManager::getAct4pointsLadderEntities()).getPacketString());
	response.push_back(S_clinit(ComplimentManager::getComplimentLadderEntities()).getPacketString());
	response.push_back(S_lev(character.getLevelProperties().levelN, character.getLevelProperties().xpN, character.getLevelProperties().levelJ,
		character.getLevelProperties().xpJ, XpConfiguration::getXpNeeded(XpType::NORMAL, character.getLevelProperties().levelN),
		XpConfiguration::getXpNeeded(XpType::JOB, character.getLevelProperties().levelJ), character.getReputationProperties().reputationAmount,
		0 /*CP : todo*/, character.getLevelProperties().xpH, character.getLevelProperties().levelH,
		XpConfiguration::getXpNeeded(XpType::HERO, character.getLevelProperties().levelH)).getPacketString());


	// TODO : add f_stash_end et c_close
	// ? Add handler sur c_close 1 qui envoie c_info_reset 


	cbRetrieveCharacter(std::make_shared<OwnCharacter>(character));
	return response;
}

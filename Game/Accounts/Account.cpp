#include "Account.h"
#include "Configuration.h"
#include "conststring.h"
#include "Network/Packets/Server/Lobby/S_clist_start.h"
#include "Network/Packets/Server/Lobby/S_clist.h"
#include "Network/Packets/Server/Lobby/S_clist_end.h"
#include "Network/Packets/Server/Messages/S_infoi.h"
#include "Network/Packets/Server/Lobby/S_success.h"
#include "Network/Packets/Server/Lobby/S_OK.h"

Account::Account(std::function<void()> CbDisconnect)
	: cbDisconnect(CbDisconnect)
	, connected(false)
	, username("")
	, password("")
	, lang(LangType::EN)
	, encryptionKey(-1)
	, authority(-1)
	, accountId(-1)
	, selectedSlot(-1)
{
}

Account::~Account()
{
}

void Account::setEncryptionKey(int EncryptionKey)
{
	encryptionKey = EncryptionKey;
}

std::string Account::getUsername() const
{
	return username;
}

std::string Account::getPassword() const
{
	return password;
}

int Account::getAccountId() const
{
	return accountId;
}

LobbyCharacter Account::getSelectedLobbyCharacter() const
{
	if (lobbyCharacters.find(selectedSlot) == lobbyCharacters.end())
		return lobbyCharacters.at(selectedSlot);
	return LobbyCharacter();
}

std::vector<std::string> Account::handlePacket(const BaseClientPacket& Packet)
{
	if (!connected)
	{
		if (username.empty())
			return handleUsernamePacket(Packet);
		else if (password.empty())
			return handlePasswordPacket(Packet);
		else if (Packet.getHeader() == "Char_NEW")
			return handle_Char_NEW(Packet);
		else if (Packet.getHeader() == "Char_NEW_JOB")
			return handle_Char_NEW_JOB(Packet);
		else if (Packet.getHeader() == "Char_DEL")
			return handle_Char_DEL(Packet);
		else if (Packet.getHeader() == "Char_REN")
			return handle_Char_REN(Packet);
		else if (Packet.getHeader() == "select")
			return handle_select(Packet);
	}
	return {};
}

std::vector<std::string> Account::handleUsernamePacket(const R_UsernamePacket& Packet)
{
	username = Packet.getUsername();
	if (username.empty() || username.find_first_not_of(ALLOWED_CHAR_USERNAME) != std::string::npos)
		cbDisconnect();
	lang = Packet.getLang();
	return {};
}

std::vector<std::string> Account::handlePasswordPacket(const R_PasswordPacket& Packet)
{
	password = Packet.getPassword();
	if (password != "thisisgfmode" || !connectAccount())
	{
		cbDisconnect();
		return {};
	}
	return loadLobbyCharacters();
}

std::vector<std::string> Account::handle_Char_NEW_JOB(const R_Char_NEW_JOB& Packet)
{
	if (!Packet.isValid())
	{
		cbDisconnect();
		return {};
	}
	std::vector<std::string> results = DatabaseManager::query("SELECT slot FROM ay_characters_lobby WHERE accountId = '" + std::to_string(accountId) + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (results.size() >= 3)
	{
		cbDisconnect();
		return {};
	}
	results = DatabaseManager::query("SELECT id FROM ay_characters_lobby WHERE account_id = '" + std::to_string(accountId) + "' AND class = '" + std::to_string(static_cast<int>(ClassType::MARTIAL_ARTIST)) + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (!results.empty())
		return { S_infoi(LOBBY_ALREADY_HAVE_MARTIAL_ARTIST, 0, 0, 0).getPacketString() };
	for (size_t i = 0; i < results.size(); i++)
	{
		short curSlot = ToNumber<short>(results[i].c_str());
		if (curSlot == Packet.getSlot())
		{
			cbDisconnect();
			return {};
		}
	}
	// Add check on 30 days after deletion
	results = DatabaseManager::query("SELECT id FROM ay_characters_lobby WHERE pseudonym = '" + Packet.getPseudonym() + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (!results.empty())
		return { S_infoi(LOBBY_CREATION_PSEUDO_TAKEN, 0, 0, 0).getPacketString() };
	createAccount(Packet, ClassType::MARTIAL_ARTIST);
	return loadLobbyCharacters(Packet.getSlot());
}

std::vector<std::string> Account::handle_Char_NEW(const R_Char_NEW& Packet)
{
	if (!Packet.isValid())
	{
		cbDisconnect();
		return {};
	}
	std::vector<std::string> results = DatabaseManager::query("SELECT slot FROM ay_characters_lobby WHERE account_id = '" + std::to_string(accountId) + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (results.size() >= 3)
	{
		cbDisconnect();
		return {};
	}
	for (size_t i = 0; i < results.size(); i++)
	{
		short curSlot = ToNumber<short>(results[i].c_str());
		if (curSlot == Packet.getSlot())
		{
			cbDisconnect();
			return {};
		}
	}
	results = DatabaseManager::query("SELECT id FROM ay_characters_lobby WHERE pseudonym = '" + Packet.getPseudonym() + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (!results.empty())
		return { S_infoi(LOBBY_CREATION_PSEUDO_TAKEN, 0, 0, 0).getPacketString() };
	createAccount(Packet, ClassType::ADVENTURER);
	return loadLobbyCharacters(Packet.getSlot());
}

std::vector<std::string> Account::handle_Char_DEL(const R_Char_DEL& Packet)
{
	if (!Packet.isValid() || (lobbyCharacters.find(Packet.getSlot()) == lobbyCharacters.end()))
	{
		cbDisconnect();
		return {};
	}
	if (Packet.getUsername() != username)
		return { S_infoi(LOBBY_DELETION_WRONG_USERNAME, 0, 0, 0).getPacketString() };
	std::vector<std::string> results = DatabaseManager::query("SELECT id FROM ay_characters_lobby WHERE account_id = " + std::to_string(accountId) + " AND slot = '" + std::to_string(Packet.getSlot()) + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'");
	if (results.empty())
	{
		cbDisconnect();
		return {};
	}
	if (!deleteAccount(Packet.getSlot()))
	{
		cbDisconnect();
		return {};
	}
	lobbyCharacters.erase(Packet.getSlot());
	std::vector<std::string> res = loadLobbyCharacters();
	res.insert(res.begin(), S_success().getPacketString());
	return res;
}

std::vector<std::string> Account::handle_Char_REN(const R_Char_REN& Packet)
{
	if (!Packet.isValid() || (lobbyCharacters.find(Packet.getSlot()) == lobbyCharacters.end()))
	{
		cbDisconnect();
		return {};
	}
	if (!lobbyCharacters.at(Packet.getSlot()).canChangePseudonym())
	{
		cbDisconnect();
		return {};
	}
	if (lobbyCharacters.at(Packet.getSlot()).getPseudonym() == Packet.getPseudonym())
		return {};
	std::vector<std::pair<SQL_TYPE, std::string>> args;
	args.push_back({ SQL_TYPE::INT, std::to_string(lobbyCharacters.at(Packet.getSlot()).getCharacterId()) }); // character id
	args.push_back({ SQL_TYPE::INT, std::to_string(Configuration::d_server_id()) }); // server id
	args.push_back({ SQL_TYPE::STRING, Packet.getPseudonym() }); // new pseudonym
	DatabaseManager::call("p_rename_character", args);
	lobbyCharacters.at(Packet.getSlot()).changePseudonym(Packet.getPseudonym());
	lobbyCharacters.at(Packet.getSlot()).setRename(false);
	return loadLobbyCharacters(Packet.getSlot());
}

std::vector<std::string> Account::handle_select(const R_select& Packet)
{
	if (!Packet.isValid() ||lobbyCharacters.find(Packet.getSlot()) == lobbyCharacters.end())
	{
		cbDisconnect();
		return {};
	}
	selectedSlot = Packet.getSlot();
	connected = true;
	// ?
	return { S_OKs().getPacketString() };
}

std::vector<std::string> Account::loadLobbyCharacters(short selected)
{
	std::vector<std::string> response;
	if (lobbyCharacters.empty())
	{
		std::vector<std::vector<std::string>> res = DatabaseManager::query("SELECT * FROM ay_characters_lobby WHERE account_id = '" + std::to_string(accountId) + "' AND server_id = '" + std::to_string(Configuration::d_server_id()) + "'", 4);
		for (size_t i = 0; i < res.size(); i++)
		{
			if (res[i].size() != 13)
				break;
			int id = ToNumber<int>(res[i][0].c_str());
			std::string pseudo = res[i][3];
			short slot = ToNumber<short>(res[i][4].c_str());
			GenderType gender = static_cast<GenderType>(ToNumber<short>(res[i][5].c_str()));
			HairStyleType hS = static_cast<HairStyleType>(ToNumber<short>(res[i][6].c_str()));
			int hC = ToNumber<int>(res[i][7].c_str());
			ClassType cl = static_cast<ClassType>(ToNumber<short>(res[i][8].c_str()));
			int level = ToNumber<short>(res[i][9].c_str());
			int levelH = ToNumber<short>(res[i][10].c_str());
			int levelJ = ToNumber<short>(res[i][11].c_str());
			bool rename = ToNumber<short>(res[i][12].c_str());
			int questAct = 1;
			int questChapter = 1;
			std::string pet = "-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.";
			std::string wornStuff = "-1.-1.-1.-1.-1.-1.-1.-1.-1.-1";
			lobbyCharacters.insert(std::pair<short, LobbyCharacter>(slot, LobbyCharacter(id, pseudo, slot, gender, hS, hC, cl, level,
				levelH, levelJ, rename, wornStuff, questAct, questChapter, pet)));
		}
	}
	response.push_back(S_clist_start(0).getPacketString());
	for (auto const& [key, val] : lobbyCharacters)
		response.push_back(S_clist(val).getPacketString());
	response.push_back(S_clist_end(selected).getPacketString());
	return response;
}

bool Account::connectAccount()
{
	std::vector<std::string> results = DatabaseManager::query("SELECT encryption_key, authority, id FROM ay_accounts WHERE username = '" + username +
		"' AND banned = 0 AND verification = 1 AND lang = " + std::to_string(static_cast<int>(lang)));
	if (results.size() != 3)
		return false;
	if (ToNumber<int>(results[0].c_str()) != encryptionKey)
		return false;
	authority = ToNumber<int>(results[1].c_str());
	accountId = ToNumber<int>(results[2].c_str());
	DatabaseManager::query("UPDATE ay_accounts_status SET connected = '1', server = '" + std::to_string(Configuration::d_server_id())
		+ "', channel = '" + std::to_string(Configuration::d_channel_id()) + "' WHERE id = '" + std::to_string(accountId) + "'");
	return true;
}

bool Account::createAccount(const R_Char_NEW& Packet, ClassType charClass)
{
	std::vector<std::pair<SQL_TYPE, std::string>> args;
	args.push_back({ SQL_TYPE::INT, std::to_string(accountId) }); // account id
	args.push_back({ SQL_TYPE::INT, std::to_string(Configuration::d_server_id()) }); // server id
	args.push_back({ SQL_TYPE::STRING, Packet.getPseudonym() }); // pseudonym
	args.push_back({ SQL_TYPE::INT, std::to_string(Packet.getSlot()) }); // slot
	args.push_back({ SQL_TYPE::INT, std::to_string(static_cast<int>(Packet.getGender())) }); // gender
	args.push_back({ SQL_TYPE::INT, std::to_string(static_cast<int>(Packet.getHairStyle())) }); // hair style
	args.push_back({ SQL_TYPE::INT, std::to_string(Packet.getHairColor()) }); // hair color
	args.push_back({ SQL_TYPE::INT, std::to_string(static_cast<int>(charClass)) }); // class
	args.push_back({ SQL_TYPE::INT, charClass == ClassType::MARTIAL_ARTIST ? "80" : "1" }); // level
	args.push_back({ SQL_TYPE::INT, "0" }); // level hero
	args.push_back({ SQL_TYPE::INT, "1" }); // level job
	args.push_back({ SQL_TYPE::INT, "0" }); // rename
	auto output = DatabaseManager::selectFunction("f_create_character", args);
	if (output.empty())
		return false;
	int charID = ToNumber<int>(output[0][0].c_str());
	LobbyCharacter lobChar(charID, Packet.getPseudonym(), Packet.getSlot(), Packet.getGender(), Packet.getHairStyle(), Packet.getHairColor(),
		charClass, charClass == ClassType::MARTIAL_ARTIST ? 80 : 1, 0, 1, false, "-1.-1.-1.-1.-1.-1.-1.-1.-1.-1", 1, 1,
		"-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.-1.");
	lobbyCharacters.insert(std::pair<int, LobbyCharacter>(Packet.getSlot(), lobChar));
	return true;
}

bool Account::deleteAccount(short slot)
{
	std::vector<std::pair<SQL_TYPE, std::string>> args;
	args.push_back({ SQL_TYPE::INT, std::to_string(accountId) }); // account id
	args.push_back({ SQL_TYPE::INT, std::to_string(Configuration::d_server_id()) }); // server id
	args.push_back({ SQL_TYPE::INT, std::to_string(slot) }); // slot
	return DatabaseManager::call("p_delete_character", args);
}
#include "ItemDatParser.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>

std::map<int, ItemStruct> ItemDat::items;

ItemDat::ItemDat(std::string DatFilename, std::string LangFilename, size_t BufferSize)
	: datFilename(DatFilename)
	, langFilename(LangFilename)
	, bufferSize(BufferSize)
{}

bool ItemDat::startParsing()
{
	return /*parseLangFile() && */parseDatFile();
}

ItemStruct ItemDat::getItemStruct(int vnum)
{
	if (items.find(vnum) == items.end())
		return ItemStruct();
	return items.at(vnum);
}

bool ItemDat::parseDatFile()
{
	std::ifstream stream = std::ifstream{ datFilename };

	if (stream.fail())
	{
		char buffer[128];
		strerror_s(buffer, errno);
		std::cout << buffer;
		return false;
	}
	char* buf = (char*)calloc(bufferSize, sizeof(char));
	std::string out;
	while (stream.read(buf, bufferSize)) {
		if (buf != 0)
			out.append(buf, 0, stream.gcount());
	}
	if (buf != 0)
		out.append(buf, 0, stream.gcount());
	stream.close();
	populate(out);
	free(buf);
	return true;
}

bool ItemDat::parseLangFile()
{
	std::ifstream stream = std::ifstream{ langFilename };

	if (stream.fail())
	{
		char buffer[128];
		strerror_s(buffer, errno);
		std::cout << buffer;
		return false;
	}
	char* buf = (char*)calloc(bufferSize, sizeof(char));
	std::string out;
	while (stream.read(buf, bufferSize)) {
		if (buf != 0)
			out.append(buf, 0, stream.gcount());
	}
	if (buf != 0)
		out.append(buf, 0, stream.gcount());
	stream.close();
	std::replace(out.begin(), out.end(), DAT_LINE_DELIMITER, DAT_COLUMN_DELIMITER);
	std::vector<std::string> pre_lang = split(out, "\t");
	for (int i = 0; i < pre_lang.size(); i = i + 2)
	{
		if (i + 1 < pre_lang.size())
		{
			lang.insert({ pre_lang[i], pre_lang[i + 1] });
		}
	}
	free(buf);


	/*
	In populate...

	if ((col[6] == "1" || col[6] == "9") && col[7] == "4" && col[40] == "1000")
		{
			if (lang.find(col[88]) != lang.end())
			{
				//std::cout << col[1] << " " << col[88] << lang.at(col[88]) << "\n\n" << std::endl;
				std::vector<std::string> t = splitSubstr(lang.at(col[88]), "[n]");
				//std::cout << t[0] << std::endl;
				int baseSpeed = -1;
				int boosterSpeed = 0;
				for (size_t a = 0; a < t.size(); a++)
				{
					if (t[a].find("Vitesse de déplacement : ") == 0)
					{
						std::cout << "a: "


						std::cout << "ID: " << col[1] << " Name: " << lang.at(col[4]) << std::endl;
						std::cout << "\t[" << t[a] << "]" << std::endl;

					}
				}

			}
		}
	*/

	return true;
}


/*
* 
 
Stuff càc : 0
Stuff dist : 1
Armure/BasNM : 2
Equipement/Aile/SkinArme/HatNM : 3
Accessoire ; 4
Stuff magique : 5
Parle/BoiteSP : 7
BoiteRaid : 8
Rune : 9
Part/Pet : 10
BoiteSPPart : 13

Dague/Epée : 0
(e_info 0 [Vnum] [Rarity] [Upgrade] [IsFixe] [Level] [MinDmg] [MaxDmg] [Preci] [ProbaCc] [DgtCc] [MuniActu] [MuniMax] [Price] [ItemIDOrangeEffect (-1 par défaut)] [ShellRarity] [OwnerID (default:0)] [NbOptionRune] {Rune} [Optionnel: [[NbOptionGravure] [GravureBroken] [NbOptionDiff] {Enchantement}])

Arc/Arba/Gun : 1
(e_info 1 [Vnum] [Rarity] [Upgrade] [IsFixe] [Level] [MinDmg] [MaxDmg] [Preci] [ProbaCc] [DgtCc] [MuniActu] [MuniMax] [Price] [ItemIDOrangeEffect (-1 par défaut)] [ShellRarity] [OwnerId (default:0)] [NbOptionRune] {Rune} [Optionnel: [[NbOptionGravure] [GravureBroken] [NbOptionDiff] {Enchantement}])

Armure/Bas nosmall/Armure part : 2
Armure :		(e_info 2 [Vnum] [Rarity] [Upgrade] [IxFixe] [Level] [DéfCàc] [DéfDist] [DéfMag] [Esq] [Price] [ItemIDOrangeEffect] [ShellRarity] [OwnerId (default:0 si runable)] [NbOptionRune] {Rune})
Bas nosmall :	(e_info 2 [Vnum] [Rarity] [Upgrade] [IsFixe] [Level] [DéfCàc] [DéfDist] [DéfMag] [Esq] [Price] [ItemIDOrangeEffect] [Commerce] [RemainingTime (h)] [vnum Fusion])

Masque/Chapeau/Gant/Botte/Aile/Skin arme/Chapeau nosmall : 3
(e_info 3 [Vnum] [Level] [DéfCàc] [DéfDist] [DéfMag] [Esq] [ResFeu] [ResEau] [ResLum] [ResObsc] [Price] [Somme] [Commerce] [RemainingTime (-1 : rien d'affiché)]) [UNIQUEMENT SI AILE/SKIN ARME/CHAPEAU NOSMALL : vnum fusion]
Commerce : 0 : rien d'affiché  1 : "Commerce possible"   2 : "Commerce impossible"

Amulettes/Fées/Bijoux : 4
Amulette :	(e_info 4 [Vnum] [Level] [RemainingTime * 10 ou NbUtilisation * 1] [Restant... (100 : nb flat), sinon temps en h (DATA[3])] [?] [Price])
Fée :	(e_info 4 [Vnum] [Elem] [Level] [?] [Xp] [Price] [?])
Bijoux :	(e_info 4 [Vnum] [Level] [MaxLevelCellon] [NbMaxCellon] [CurrentNbCellon]] [Price] { [EffectCellon] [LvCellon] [Value] })
e_info 4 4057 60 108000 1001 0 10000

EffectCellon : 0 : hp 1 : mp 2 : Régen hp 3 : Régen Mp 4 : Conso mp 5 : Dégâts cc

Baguette/Baguette partenaire : 5
e_info 5 [Vnum] [Rarity] [Upgrade] [IsFixe] [Level] [DgtMin] [DgtMax] [Concentration] [ProbaCc] [DgtCc] [MuniActu] [MuniMax] [Price] [ItemIDOrangeEffect] [ShellRarity] [OwnerId (default:0 si runable)] [NbOptionRune] {Rune} [Optionnel: [[NbOptionGravure] [GravureBroken] [NbOptionDiff] {Enchantement}])

Perle de pet/SP : 7
perle :	(e_info 7 [Vnum] [?] [MobId ] [Level] [XpCurrent] [XpMax] [NvAtk] [NvDéf])
sp :	(e_info 7 [Vnum] [?] [ItemId] [Level] [XpCurrent] [XpMax] [Upgrade] [Atk] [Déf] [Elé] [Hp] [PtsRestant] [Amélio] [ResFeu] [ResEau] [ResLum] [ResObsc] [AmélioAtk] [AmélioDéf] [AmélioElé] [AmélioHp] [AmélioResFeu] ["eau] ["lum] ["obsc])

Boîte de raid Glacerus/Draco : 8	
(e_info 8 [Vnum] [RaidId] [Rarity])

Runes : 9
(e_info 9 [Vnum] [Level] [Rarity] [Price] [NbOption] {x.x.x})

Pet/Partner : 
(e_info 10 [MonsterVnum] [Lvl] [Elem] [AtkType] [Element%] [AtkUP] [DmgMin] [DmgMax] [Concen] [ChanceCc] [DgtCc] [DéfUP] [DéfCàc] [EsqCàc] [DéfDist] [EsqDist] [DéfMag] [ResFeu] [ResEau] [ResLum] [ResOBsc] [MaxHP] [MaxMP] [MorphId (for partner skin)] [Name (if mate)] [10000 + x = ConstString] [?])

SP Partenaires boîtées : 13
(e_info 13 [Vnum] 1 [ItemId] [Elem 0: Aucun1: feu ...] [SkillId] [SkillRank] [SkillId] [SkillRank] [SkillId] [SkillRank])
SkillRank et SkillId à 0 par défaut   1F 2E 3D 4C 5B 6A 7S*/


// TODO : add vehicle property
void ItemDat::populate(std::string& data)
{
	std::replace(data.begin(), data.end(), DAT_LINE_DELIMITER, DAT_COLUMN_DELIMITER);
	std::vector<std::string> entity = split(data, DAT_ENTITY_DELIMITER);
	for (size_t i = 0; i < entity.size(); i++) // Every entity
	{
		std::vector<std::string> col = split(entity[i], std::string(1, DAT_COLUMN_DELIMITER));
		if (col.size() < 89)
			continue;
		ItemStruct itm(col);
		items.insert({ itm.getVnum(), itm });
		// col[0] = "VNUM"
		
		// col[1] = vnum
		// col[2] = price

		// col[3] = "NAME"

		// col[4] = nameZts

		// col[5] = "INDEX"

		// col[6] = InventoryPart
		// col[7] = Nosbazard category
/*k : 6   0
k : 7   0
k : 8   0
k : 9   0
k : 10  1
k : 11  0*/
/* Item.dat function parsing

* 14 : Attack type
* 15 : Class that can equip
* 20 : Not Soldable ?
* 21 : Not dropable ?
* 22 : Not tradable ?
* 29 : Parameter
* 88 : Line Description
* 89 : Description's identifier (ztsXXXXXe)
*/



		// col[12] = "TYPE"

		// col[13] = AttackType
		// col[14] = Class that can equip

		// col[15] = "FLAG"

		// col[19] = Not soldave ?
		// col[20] = Not dropable ?
		// col[21] = Not tradable
		// col[34] = Buyable with reputation
		// col[35] = IsHeroic
		// col[38] = IsLimited ?

		// col[39] = "DATA"

		// col[60] = "BUFF"

		// col[86] = "LINEDESC"


		// col[89] = "END"
			/*
INDEX
k : 6   0
k : 7   0
k : 8   0
k : 9   0
k : 10  1
k : 11  0
TYPE
k : 13  0
k : 14  1
FLAG
k : 16  0
k : 17  0
k : 18  0
k : 19  0
k : 20  0
k : 21  0
k : 22  0
k : 23  0
k : 24  0
k : 25  0
k : 26  0
k : 27  0
k : 28  0
k : 29  0
k : 30  0
k : 31  0
k : 32  0
k : 33  0
k : 34  0
k : 35  0
k : 36  0
k : 37  0
k : 38  0
DATA
k : 40  1
k : 41  20
k : 42  28
k : 43  20
k : 44  4
k : 45  70
k : 46  0
k : 47  0
k : 48  0
k : 49  0
k : 50  0
k : 51  0
k : 52  0
k : 53  0
k : 54  0
k : 55  0
k : 56  0
k : 57  0
k : 58  0
k : 59  0
BUFF
k : 61  -1
k : 62  80
k : 63  0
k : 64  0
k : 65  0
k : 66  0
k : 67  0
k : 68  0
k : 69  0
k : 70  0
k : 71  0
k : 72  0
k : 73  0
k : 74  0
k : 75  0
k : 76  0
k : 77  0
k : 78  0
k : 79  0
k : 80  0
k : 81  0
k : 82  0
k : 83  0
k : 84  0
k : 85  0
LINEDESC
k : 87  1
k : 88  zts4e
END
			*/
	}
}

ItemStruct::ItemStruct(std::vector<std::string> d)
{
	// col[0] = "VNUM"
	vnum = ToNumber<int>(d[1].c_str());
	price = ToNumber<int>(d[2].c_str());
	
	// col[3] = "NAME"
	nameIdentifier = d[4];

	// col[5] = "INDEX"
	inventoryType = static_cast<InventoryType>(ToNumber<int>(d[6].c_str()));
	nbType = static_cast<NosbazardType>(ToNumber<int>(d[7].c_str()));
	Unknown1 = ToNumber<int>(d[8].c_str());
	charSheetSlot = ToNumber<int>(d[9].c_str());
	imageId = ToNumber<int>(d[10].c_str());
	morphId = ToNumber<int>(d[11].c_str());

	// col[12] = "TYPE"
	atkType = static_cast<AttackType>(ToNumber<int>(d[13].c_str()));
	classHolder = static_cast<ClassCanHoldItemType>(ToNumber<int>(d[14].c_str()));

	// col[15] = "FLAG"

	soldable = ToNumber<int>(d[19].c_str());
	dropable = ToNumber<int>(d[20].c_str());
	tradable = ToNumber<int>(d[21].c_str());

	miniland = ToNumber<int>(d[22].c_str());
	warehouse = ToNumber<int>(d[23].c_str());
	warnUse = ToNumber<int>(d[24].c_str());

	buyableWithReput = ToNumber<int>(d[34].c_str());
	heroic = ToNumber<int>(d[35].c_str());
	limited = ToNumber<int>(d[38].c_str());

	// col[39] = "DATA"
	level = ToNumber<int>(d[40].c_str());
	defMelee = dmgMin = ToNumber<int>(d[41].c_str());
	defDist = dmgMax = ToNumber<int>(d[42].c_str());
	defMag = preciConcen = ToNumber<int>(d[43].c_str());
	probaCc = dodge = ToNumber<int>(d[44].c_str());
	dmgCc = resFire = ToNumber<int>(d[45].c_str());
	resWater = ToNumber<int>(d[46].c_str());
	resLight = ToNumber<int>(d[47].c_str());
	// 0
	resDark = ToNumber<int>(d[49].c_str());

	// col[60] = "BUFF"
	// TODO : implement Bcard
	// 61 : bcard 62 : val1 63 : val2 64 : bcard subtype 65 : Null terminated
	// 66 : bcard...
	// 85 null terminated

	// col[86] = "LINEDESC"
	numberLineDescription = ToNumber<int>(d[87].c_str());
	descriptionIdentifier = d[88]; // Some items have 2

	// col[89] || col[90] = "END"
}

int ItemStruct::getVnum() const
{
	return vnum;
}

int ItemStruct::getPriceGold() const
{
	return (-1 * buyableWithReput) + (price * !buyableWithReput);
}

int ItemStruct::getPriceReputation() const
{
	return (-1 * !buyableWithReput) + (price * buyableWithReput);
}

int ItemStruct::getPriceGeneral() const
{
	return price;
}

InventoryType ItemStruct::getInventoryType() const
{
	return inventoryType;
}

NosbazardType ItemStruct::getNosbazardType() const
{
	return nbType;
}

int ItemStruct::getItemImageId() const
{
	return imageId;
}

int ItemStruct::getItemMorphId() const
{
	return morphId;
}

AttackType ItemStruct::getAttackType() const
{
	return atkType;
}

ClassCanHoldItemType ItemStruct::getClassHolder() const
{
	return classHolder;
}

bool ItemStruct::isSoldable() const
{
	return soldable;
}

bool ItemStruct::isDropable() const
{
	return dropable;
}

bool ItemStruct::isTradable() const
{
	return tradable;
}

bool ItemStruct::isMiniland() const
{
	return miniland;
}

bool ItemStruct::isWarehouse() const
{
	return warehouse;
}

bool ItemStruct::isWarnUse() const
{
	return warnUse;
}

bool ItemStruct::isBuyableWithReput() const
{
	return buyableWithReput;
}

bool ItemStruct::isHeroic() const
{
	return heroic;
}

bool ItemStruct::isLimited() const
{
	return limited;
}

int ItemStruct::getLevel() const
{
	return level;
}

int ItemStruct::getDefMelee() const
{
	return defMelee;
}

int ItemStruct::getDmgMin() const
{
	return dmgMin;
}

int ItemStruct::getDefDist() const
{
	return defDist;
}

int ItemStruct::getDmgMax() const
{
	return dmgMax;
}

int ItemStruct::getDefMag() const
{
	return defMag;
}

int ItemStruct::getPreciConcen() const
{
	return preciConcen;
}

int ItemStruct::getProbaCc() const
{
	return probaCc;
}

int ItemStruct::getDodge() const
{
	return dodge;
}

int ItemStruct::getDmgCc() const
{
	return dmgCc;
}

int ItemStruct::getResFire() const
{
	return resFire;
}

int ItemStruct::getResWater() const
{
	return resWater;
}

int ItemStruct::getResLight() const
{
	return resLight;
}

int ItemStruct::getResDark() const
{
	return resDark;
}

int ItemStruct::getEInfoFirstValue() const
{
	if (isDagger() || isSword() || isAdventurerSword())
		return 0;
	else if (isBow() || isCrossbow() || isGun() || isCatapult())
		return 1;
	else if (isArmor() || isCostNosmall() || isPartnerArmor())
		return 2;
	else if (isMask() || isHat() || isGlove() || isShoe() || isWing() || isWeaponSkin() || isHatNosmall())
		return 3;
	else if (isAmulet() || isFairy() || isNecklace() || isRing() || isBracelet())
		return 4;
	else if (isStaff() || isPartnerStaff())
		return 5;
	// 6 ?
	else if (isPet() || isPartner())
		return 7;
	else if (isRaidBox())
		return 8;
	else if (isShellArmor() || isShellWeapon())
		return 9;
	else if (isVehicleBooster())
		return 11;
	// 12 ?
	// 13 = Stored Partner SP Card
	return 0;
}

bool ItemStruct::isAdventurerSword() const
{
	// 0 0 0 0
	// 0 1
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 0 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ADVENTURER;
}

bool ItemStruct::isStaff() const
{
	// 0 0 9 0
	// 2 8
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 9 && charSheetSlot == 0 &&
		atkType == AttackType::MAGIC && classHolder == ClassCanHoldItemType::MAGICIAN;
}

bool ItemStruct::isSword() const
{
	// 0 0 1 0
	// 0 2
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 1 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::SWORDSMAN;
}

bool ItemStruct::isBow() const
{
	// 0 0 6 0
	// 1 4
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 6 && charSheetSlot == 0 &&
		atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::ARCHER;
}

bool ItemStruct::isFeast() const
{
	// 4 0 4 0
	// 0 16
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 4 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::MARTIAL_ARTIST;
}

bool ItemStruct::isCatapult() const
{
	// 0 0 5 5
	// 1 1
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 5 && charSheetSlot == 5 &&
		atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::ADVENTURER;
}

bool ItemStruct::isGun() const
{
	// 0 0 8 5
	// 1 8
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 8 && charSheetSlot == 5 &&
		atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::MAGICIAN;
}

bool ItemStruct::isCrossbow() const
{
	// 0 0 5 5
	// 1 1
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 5 && charSheetSlot == 5 &&
		atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::SWORDSMAN;
}

bool ItemStruct::isDagger() const
{
	// 0 0 3 5
	// 0 4
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 3 && charSheetSlot == 5 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ARCHER;
}

bool ItemStruct::isMedal() const
{
	// 4 0 11 5
	// 1 16
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 11 && charSheetSlot == 5 &&
		atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::MARTIAL_ARTIST;
}

bool ItemStruct::isArmor() const
{
	// 0 1 X 1
	// X X
	return isEquipment() && nbType == NosbazardType::ARMOR && charSheetSlot == 1;
}

bool ItemStruct::isCostNosmall() const
{
	// 0 2 4 13
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 4 && charSheetSlot == 13 &&
	atkType == AttackType::MELEE;
}

bool ItemStruct::isHatNosmall() const
{
	// 0 2 5 14
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 5 && charSheetSlot == 14 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isMask() const
{
	// 0 2 1 9
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 1 && charSheetSlot == 9 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isHat() const
{
	// 0 2 0 2
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 0 && charSheetSlot == 2 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isGlove() const
{
	// 0 2 2 3
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 2 && charSheetSlot == 3 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isShoe() const
{
	// 0 2 3 4
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 3 && charSheetSlot == 4 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isAmulet() const
{
	// 0 3 4 11
	// 0 X
	return isEquipment() && nbType == NosbazardType::ACCESSORIES && Unknown1 == 4 && charSheetSlot == 11 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isFairy() const
{
	// 0 3 3 10
	// 0 X
	return isEquipment() && nbType == NosbazardType::ACCESSORIES && Unknown1 == 3 && charSheetSlot == 10 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isRing() const
{
	// 0 3 1 7
	// 0 X
	return isEquipment() && nbType == NosbazardType::ACCESSORIES && Unknown1 == 1 && charSheetSlot == 7 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isBracelet() const
{
	// 0 3 2 8
	// 0 X
	return isEquipment() && nbType == NosbazardType::ACCESSORIES && Unknown1 == 2 && charSheetSlot == 8 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isNecklace() const
{
	// 0 3 0 6
	// 0 X
	return isEquipment() && nbType == NosbazardType::ACCESSORIES && Unknown1 == 0 && charSheetSlot == 6 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isWing() const
{
	// 0 2 7 16
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 7 && charSheetSlot == 16 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isWeaponSkin() const
{
	// 0 2 6 15
	// 0 X
	return isEquipment() && nbType == NosbazardType::EQUIPMENT && Unknown1 == 6 && charSheetSlot == 15 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isPartnerWeapon() const
{
	// 0 0 12 0
	// X 0
	return isEquipment() && nbType == NosbazardType::WEAPON && Unknown1 == 12 && charSheetSlot == 0 &&
		classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isPartnerStaff() const
{
	return isPartnerWeapon() && atkType == AttackType::MAGIC;
}

bool ItemStruct::isPartnerSword() const
{
	return isPartnerWeapon() && atkType == AttackType::MELEE;
}

bool ItemStruct::isPartnerBow() const
{
	return isPartnerWeapon() && atkType == AttackType::RANGE;
}

bool ItemStruct::isPartnerArmor() const
{
	// 0 1 4 1
	// X 0
	return isEquipment() && nbType == NosbazardType::ARMOR && Unknown1 == 4 && charSheetSlot == 1 &&
		classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isPartnerArmorRange() const
{
	return isPartnerArmor() && atkType == AttackType::RANGE;
}

bool ItemStruct::isPartnerArmorMelee() const
{
	return isPartnerArmor() && atkType == AttackType::MELEE;
}

bool ItemStruct::isPartnerArmorMage() const
{
	return isPartnerArmor() && atkType == AttackType::MAGIC;
}

bool ItemStruct::isPet() const
{
	// 0 5 0 0
	// 0 0
	return isEquipment() && nbType == NosbazardType::MATE_SPHOLDER_POTION_RAIDBOX && Unknown1 == 0 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isPartner() const
{
	// 0 5 1 0
	// 0 0
	return isEquipment() && nbType == NosbazardType::MATE_SPHOLDER_POTION_RAIDBOX && Unknown1 == 1 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isSp() const
{
	// 0 4 1 12
	// 0 X
	return isEquipment() && nbType == NosbazardType::VEHICLE_SP && Unknown1 == 1 && charSheetSlot == 12 &&
		atkType == AttackType::MELEE;
}

bool ItemStruct::isSpMage() const
{
	return isSp() && classHolder == ClassCanHoldItemType::MAGICIAN;
}

bool ItemStruct::isSpSwordsman() const
{
	return isSp() && classHolder == ClassCanHoldItemType::SWORDSMAN;
}

bool ItemStruct::isSpArcher() const
{
	return isSp() && classHolder == ClassCanHoldItemType::ARCHER;
}

bool ItemStruct::isSpMartialArtist() const
{
	return isSp() && classHolder == ClassCanHoldItemType::MARTIAL_ARTIST;
}

bool ItemStruct::isSpCommon() const
{
	return isSp() && (classHolder == ClassCanHoldItemType::ALL || classHolder == ClassCanHoldItemType::ALL2);
}

bool ItemStruct::isSpCommonExcludingAdventurer() const
{
	return isSp() && classHolder == ClassCanHoldItemType::ALL_EXCEPT_ADV;
}

bool ItemStruct::isRaidBox() const
{
	// 4 5 3 0
	// 1 0
	return (isEquipment() && nbType == NosbazardType::MATE_SPHOLDER_POTION_RAIDBOX && Unknown1 == 3 && charSheetSlot == 0 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL)
		||
	// 0 4 3 -1 302 -1
	// 1 0
		(isEquipment() && nbType == NosbazardType::MATE_SPHOLDER_POTION_RAIDBOX && Unknown1 == 3 && charSheetSlot == -1 && imageId == 302 && morphId == -1 &&
			atkType == AttackType::RANGE && classHolder == ClassCanHoldItemType::ALL);
}

bool ItemStruct::isShellArmor() const
{
	// 0 6 1 -1
	// 0 0
	return isEquipment() && nbType == NosbazardType::SHELL && Unknown1 == 1 && charSheetSlot == -1 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isShellWeapon() const
{
	// 0 6 0 -1
	// 0 0
	return isEquipment() && nbType == NosbazardType::SHELL && Unknown1 == 0 && charSheetSlot == -1 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isVehicleBooster() const
{
	// 4 5 7
	// 0 0
	return isEquipment() && nbType == NosbazardType::MATE_SPHOLDER_POTION_RAIDBOX && Unknown1 == 7 &&
		atkType == AttackType::MELEE && classHolder == ClassCanHoldItemType::ALL;
}

bool ItemStruct::isEquipment() const
{
	return (inventoryType == InventoryType::EQUIPMENT || inventoryType == InventoryType::EQUIPMENT_POST_A5 || inventoryType == InventoryType::EQUIPMENT_L);
}

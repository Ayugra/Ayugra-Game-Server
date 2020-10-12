#pragma once
#include <string>
#include <vector>
#include <map>
#include "Game/Types/InventoryType.h"
#include "Game/Types/NosbazardType.h"
#include "Game/Types/AttackType.h"
#include "Game/Types/ClassType.h"

class ItemStruct
{
public:
    ItemStruct() : vnum(-1) {}
    ItemStruct(std::vector<std::string> data);

    // VNUM
    int getVnum() const;
    int getPriceGold() const; int getPriceReputation() const; int getPriceGeneral() const;
    // Name : no need for now
    // INDEX
    InventoryType getInventoryType() const;
    NosbazardType getNosbazardType() const;
    // ?
    int getItemImageId() const;
    int getItemMorphId() const;

    // TYPE
    AttackType getAttackType() const;
    ClassCanHoldItemType getClassHolder() const;
    // FLAG
    bool isSoldable() const;
    bool isDropable() const;
    bool isTradable() const;
    bool isMiniland() const;
    bool isWarehouse() const;
    bool isWarnUse() const;
    bool isBuyableWithReput() const;
    bool isHeroic() const;
    bool isLimited() const;
    // DATA
    int getLevel() const;
    int getDefMelee() const;    int getDmgMin() const;
    int getDefDist() const;     int getDmgMax() const;
    int getDefMag() const;      int getPreciConcen() const;
    int getProbaCc() const;     int getDodge() const;
    int getDmgCc() const;       int getResFire() const;
    int getResWater() const;
    int getResLight() const;
    int getResDark() const;
    // BUFF
    // LINEDESC : no need for now
    // END


    int getEInfoFirstValue() const;

    bool isAdventurerSword() const;
    bool isStaff() const;
    bool isSword() const;
    bool isBow() const;
    bool isFeast() const;

    bool isCatapult() const;
    bool isGun() const;
    bool isCrossbow() const;
    bool isDagger() const;
    bool isMedal() const;

    bool isArmor() const;

    bool isCostNosmall() const;
    bool isHatNosmall() const;
    bool isWing() const;
    bool isWeaponSkin() const;

    bool isMask() const;
    bool isHat() const;
    bool isGlove() const;
    bool isShoe() const;

    bool isAmulet() const;
    bool isFairy() const;
    bool isRing() const;
    bool isBracelet() const;
    bool isNecklace() const;

    bool isPartnerWeapon() const;
    bool isPartnerStaff() const;
    bool isPartnerSword() const;
    bool isPartnerBow() const;

    bool isPartnerArmor() const;
    bool isPartnerArmorRange() const;
    bool isPartnerArmorMelee() const;
    bool isPartnerArmorMage() const;

    bool isPet() const;
    bool isPartner() const;

    bool isSp() const;
    bool isSpMage() const;
    bool isSpSwordsman() const;
    bool isSpArcher() const;
    bool isSpMartialArtist() const;
    bool isSpCommon() const;
    bool isSpCommonExcludingAdventurer() const;

    bool isRaidBox() const;
    bool isShellArmor() const;
    bool isShellWeapon() const;
    bool isVehicleBooster() const;

private:
    // VNUM
    int vnum;
    int price;
    // NAME
    std::string nameIdentifier;
    // INDEX
    InventoryType inventoryType;
    NosbazardType nbType;
    int Unknown1;
    int charSheetSlot;
    int imageId;
    int morphId;
    // TYPE
    AttackType atkType;
    ClassCanHoldItemType classHolder;
    // FLAG
    bool soldable;
    bool dropable;
    bool tradable;
    bool miniland;
    bool warehouse;
    bool warnUse;
    bool buyableWithReput;
    bool heroic;
    bool limited;
    // DATA
    int level;
    int defMelee,   dmgMin;
    int defDist,    dmgMax;
    int defMag,     preciConcen;
    int probaCc,    dodge;
    int dmgCc,      resFire;
    int resWater;
    int resLight;
    int resDark;
    // BUFF
    // LINEDESC
    int numberLineDescription;
    std::string descriptionIdentifier;
    // END


    bool isEquipment() const;
};

class ItemDat
{
public:
    ItemDat(std::string DatFilename, std::string LangFilename, size_t BufferSize = 65536);
    bool startParsing();
    static ItemStruct getItemStruct(int vnum);

private:
    bool parseDatFile();
    bool parseLangFile();

    void populate(std::string& data);

    std::string datFilename, langFilename;
    static std::map<int, ItemStruct> items;
    std::map<std::string, std::string> lang;
    size_t bufferSize;


    const std::string DAT_ENTITY_DELIMITER  = "#========================================================";
    const char DAT_LINE_DELIMITER    = '\x0D';
    const char DAT_COLUMN_DELIMITER  = '\t';
};

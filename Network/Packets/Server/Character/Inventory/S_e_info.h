#pragma once
#pragma once
#include "Network/Packets/BaseServerPacket.h"
#include "Game/Accounts/Character/Attributes/Inventory/Item.h"
#include "Configuration/GameFiles/ItemDatParser.h"

class S_e_info : public BaseServerPacket
{
public:
	S_e_info(Item item)
		: BaseServerPacket("e_info")
	{
		ItemStruct itm = ItemDat::getItemStruct(item.getVnum());
		if (itm.getVnum() != -1)
		{
			int eiVal = itm.getEInfoFirstValue();
			packet += " " + std::to_string(eiVal);
			packet += " " + std::to_string(itm.getVnum());
			if (eiVal == 0)
			{
				packet += " " + std::to_string(item.getRarity());
				packet += " " + std::to_string(item.getUpgrade());
				packet += " " + std::to_string(0); // TODO : IsFixe
				packet += " " + std::to_string(itm.getLevel());
				packet += " " + std::to_string(itm.getDmgMin() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgMax() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getPreciConcen() + 50); // TODO : value in db
				packet += " " + std::to_string(itm.getProbaCc()); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgCc());
				packet += " " + std::to_string(itm.getPriceGeneral());
				packet += " " + std::to_string(-1); // Effect Orange (-1 = of vnum), used for partner item
				packet += " " + std::to_string(itm.isHeroic() ? 0 : item.getShell().getRarity());
				int nbEffect = item.getShell().getNumberEffect();
				packet += " " + std::to_string(nbEffect > 0 ? item.getOwnerId() : 0);
				packet += " " + std::to_string(nbEffect);
				if (nbEffect > 0)
					packet += " " + item.getShell().getData();
				if (item.getEnhancement().getNumberUpgrade() > 0)
				{
					packet += " " + std::to_string(item.getEnhancement().getNumberUpgrade());
					packet += " " + std::to_string(item.getEnhancement().isBroken());
					packet += " " + std::to_string(item.getEnhancement().getNumberOptions());
					packet += " " + item.getEnhancement().getData();
				}
			}
			else if (eiVal == 1)
			{
				packet += " " + std::to_string(item.getRarity());
				packet += " " + std::to_string(item.getUpgrade());
				packet += " " + std::to_string(0); // TODO : IsFixe
				packet += " " + std::to_string(itm.getLevel());
				packet += " " + std::to_string(itm.getDmgMin() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgMax() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getPreciConcen() + 50); // TODO : value in db
				packet += " " + std::to_string(itm.getProbaCc()); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgCc());
				packet += " " + std::to_string(0); // Ammo current
				packet += " " + std::to_string(100); // Ammo max
				packet += " " + std::to_string(itm.getPriceGeneral());
				packet += " " + std::to_string(-1); // Effect Orange (-1 = of vnum), used for partner item
				packet += " " + std::to_string(itm.isHeroic() ? 0 : item.getShell().getRarity());
				int nbEffect = item.getShell().getNumberEffect();
				packet += " " + std::to_string(nbEffect > 0 ? item.getOwnerId() : 0);
				packet += " " + std::to_string(nbEffect);
				if (nbEffect > 0)
					packet += " " + item.getShell().getData();
				if (item.getEnhancement().getNumberUpgrade() > 0)
				{
					packet += " " + std::to_string(item.getEnhancement().getNumberUpgrade());
					packet += " " + std::to_string(item.getEnhancement().isBroken());
					packet += " " + std::to_string(item.getEnhancement().getNumberOptions());
					packet += " " + item.getEnhancement().getData();
				}
			}
			else if (eiVal == 2)
			{
				packet += " " + std::to_string(item.getRarity());
				packet += " " + std::to_string(item.getUpgrade());
				packet += " " + std::to_string(0); // TODO : IsFixe
				packet += " " + std::to_string(itm.getLevel());
				packet += " " + std::to_string(itm.getDefMelee() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getDefDist() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getDefMag() + 50); // TODO : value in db
				packet += " " + std::to_string(itm.getDodge()); // TODO : value in db
				packet += " " + std::to_string(itm.getPriceGeneral());
				packet += " " + std::to_string(-1); // Effect Orange (-1 = of vnum), used for partner item
				if (itm.isCostNosmall())
				{
					packet += " " + std::to_string(0); // TODO : commerce (stock if already used)
					packet += " " + std::to_string(-1); // TODO : remaining time (h)
					packet += " " + std::to_string(0); // TODO : fusion
				}
				else
				{
					packet += " " + std::to_string(itm.isHeroic() ? 0 : item.getShell().getRarity());
					int nbEffect = item.getShell().getNumberEffect();
					packet += " " + std::to_string(nbEffect > 0 ? item.getOwnerId() : 0);
					packet += " " + std::to_string(nbEffect);
					if (nbEffect > 0)
						packet += " " + item.getShell().getData();
				}
			}
			else if (eiVal == 3)
			{
				packet += " " + std::to_string(itm.getLevel());
				packet += " " + std::to_string(itm.getDefMelee());
				packet += " " + std::to_string(itm.getDefDist());
				packet += " " + std::to_string(itm.getDefMag());
				packet += " " + std::to_string(itm.getDodge()); // TODO : value in db
				packet += " " + std::to_string(itm.getResFire()); // TODO : value in db
				packet += " " + std::to_string(itm.getResWater()); // TODO : value in db
				packet += " " + std::to_string(itm.getResLight()); // TODO : value in db
				packet += " " + std::to_string(itm.getResDark());
				packet += " " + std::to_string(itm.getPriceGeneral());
				packet += " " + std::to_string(0); // TODO : sum
				packet += " " + std::to_string(0); // TODO : trade...
				packet += " " + std::to_string(-1); // TODO : remaining time
				if (itm.isWing() || itm.isWeaponSkin() || itm.isHatNosmall())
				{
					packet += " " + std::to_string(-1); // TODO : fusion costume
				}
			}
			else if (eiVal == 4)
			{
				if (itm.isAmulet())
				{
					packet += " " + std::to_string(100); // TODO : Remaining times
					packet += " " + std::to_string(100); // TODO : remaining type... (100 : nb flat, etc) DATA[3]
					packet += " " + std::to_string(0); // ?
					packet += " " + std::to_string(itm.getPriceGeneral());
				}
				else if (itm.isFairy())
				{
					packet += " " + std::to_string(1); // TODO : elem
					packet += " " + std::to_string(80); // TODO : level
					packet += " " + std::to_string(0); // ?
					packet += " " + std::to_string(0); // TODO : xp
					packet += " " + std::to_string(itm.getPriceGeneral());
					packet += " " + std::to_string(0); // ?
				}
				else if (itm.isRing() || itm.isNecklace() || itm.isBracelet())
				{
					packet += " " + std::to_string(80); // TODO : level
					packet += " " + std::to_string(9); // TODO : max lvl cellon
					packet += " " + std::to_string(0); // TODO : nb max cellon
					packet += " " + std::to_string(0); // TODO : current nb cellon
					packet += " " + std::to_string(itm.getPriceGeneral());

					/*
					Here, array of CellonEffect : { [EffectCellon] [LvCellon] [Value] }
					EffectCellon : 0 : hp 1 : mp 2 : regen hp 3 : regen mp 4 : conso mp 5 : dmg cc
					*/
				}
			}
			else if (eiVal == 5)
			{
				packet += " " + std::to_string(item.getRarity());
				packet += " " + std::to_string(item.getUpgrade());
				packet += " " + std::to_string(0); // TODO : IsFixe
				packet += " " + std::to_string(itm.getLevel());
				packet += " " + std::to_string(itm.getDmgMin() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgMax() + 200); // TODO : value in db
				packet += " " + std::to_string(itm.getPreciConcen() + 50); // TODO : value in db
				packet += " " + std::to_string(itm.getProbaCc()); // TODO : value in db
				packet += " " + std::to_string(itm.getDmgCc()); // TODO : value in db
				packet += " " + std::to_string(0); // Ammo current
				packet += " " + std::to_string(100); // Ammo max
				packet += " " + std::to_string(itm.getPriceGeneral());
				packet += " " + std::to_string(-1); // Effect Orange (-1 = of vnum), used for partner item
				packet += " " + std::to_string(itm.isHeroic() ? 0 : item.getShell().getRarity());
				int nbEffect = item.getShell().getNumberEffect();
				packet += " " + std::to_string(nbEffect > 0 ? item.getOwnerId() : 0);
				packet += " " + std::to_string(nbEffect);
				if (nbEffect > 0)
					packet += " " + item.getShell().getData();
				if (item.getEnhancement().getNumberUpgrade() > 0)
				{
					packet += " " + std::to_string(item.getEnhancement().getNumberUpgrade());
					packet += " " + std::to_string(item.getEnhancement().isBroken());
					packet += " " + std::to_string(item.getEnhancement().getNumberOptions());
					packet += " " + item.getEnhancement().getData();
				}
			}
			else if (eiVal == 6)
			{
				// Nothing found for now
			}
			else if (eiVal == 7)
			{
				// TODO : Pearl and SP
			}
			else if (eiVal == 8)
			{
				// TODO : raid boxex
			}
			else if (eiVal == 9)
			{
				packet += " " + std::to_string(itm.getLevel()); // TODO : Get from item not itm
				packet += " " + std::to_string(item.getRarity());
				packet += " " + std::to_string(itm.getPriceGeneral());
				int nbEffect = item.getShell().getNumberEffect();
				packet += " " + std::to_string(nbEffect);
				if (nbEffect > 0)
					packet += " " + item.getShell().getData();
			}
			else if (eiVal == 11)
			{
			// Boosteur (e_info 11 [Vnum] [Activated] [Hour])
			}
			else if (eiVal == 12)
			{
			// Nothing found for now
			}
			else if (eiVal == 13)
			{
			/*
			SP Partenaires boîtées : 13
(e_info 13 [Vnum] 1 [ItemId] [Elem 0: Aucun1: feu ...] [SkillId] [SkillRank] [SkillId] [SkillRank] [SkillId] [SkillRank])
SkillRank et SkillId à 0 par défaut   1F 2E 3D 4C 5B 6A 7S
			*/
			}
			else if (eiVal == 14)
			{
			// Nothing found for now
			}
			else if (eiVal == 15)
			{
			// Nothing found for now
			}
		}
	}

	S_e_info()
	{
		// Mate/Monster

		/*
		Pet/Partner :
(e_info 10 [MonsterVnum] [Lvl] [Elem] [AtkType] [Element%] [AtkUP] [DmgMin] [DmgMax] [Concen] [ChanceCc] [DgtCc] [DéfUP] [DéfCàc] [EsqCàc] [DéfDist] [EsqDist] [DéfMag] [ResFeu] [ResEau] [ResLum] [ResOBsc] [MaxHP] [MaxMP] [MorphId (for partner skin)] [Name (if mate)] [10000 + x = ConstString] [?])

		*/
	}
};

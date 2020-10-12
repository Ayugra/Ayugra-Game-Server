#include "Enhancement.h"
#include "Utils.h"

Enhancement::Enhancement(std::string Data, bool Broken)
	: data(Data)
	, numberOptions(0)
	, numberUpgrade(0)
	, broken(Broken)
{
	if (!data.empty())
	{
		std::vector<std::string> effects = split(Data, " ");
		numberOptions = effects.size();
		for (size_t i = 0; i < effects.size(); i++)
		{
			std::vector<std::string> effValues = split(effects[i], ".");
			if (effValues.size() != 5)
				continue;
			numberUpgrade += ToNumber<int>(effValues[4].c_str());
			// { [BcardVnum].[BcardSubtype].[BcardValue * 4].[CardVnum * 4].[NbProc] }
			// TODO after implementing Bcard system
			/*
3.0.160.0.2		ATK +40
4.0.80.0.1      PRECI +20
7.4.60.0.2      ELE +15
9.0.80.0.1      DEF +20
13.0.28.0.3		RESISTANCE +7%
33.0.3200.0.3   HP +800
33.1.1600.0.2   MP +400
44.1.-4.0.1     DEF +1%
44.1.4.0.1      ATK +1%
102.4.4.0.1     PRECI +1%
104.3.4.0.1     NOSMATE 1%
105.0.4.7600.1  1% PROBA nv effet * 18 DGT POUVOIR DE L'APOCALYPSE + POUVOIR DE L'APOCALYPSE nv1
105.1.8.7624.2  2% PROBA POUVOIR DE LA REFLEXION nv2
105.2.8.7644.2  2% PROBA nv effet * 15 DGT POUVOIR DU LOUP + POUVOIR DU LOUP nv2
105.3.4.7660.1  1% PROBA REPOUSSER 4 CASES + POUVOIR DU CONTRECOUP nv1
105.4.4.7680.1  1% PROBA nv effet * 17 DGT POUVOIR DE L'EXPLOSION + POUVOIR DE L'EXPLOSION nv1
106.0.8.7704.2  2% PROBA POUVOIR DE L'AGILITE nv2
106.1.4.7720.1  1% PROBA nv effet * 18 DGT POUVOIR DE L'ECLAIR + POUVOIR DE L'ECLAIR nv1
106.2.4.7740.1  1% PROBA POUVOIR DE LA MALEDICTION nv1
106.3.4.7760.1  1% PROBA nv effet * 23 POUVOIR DE L'OURS + POUVOIR DE L'OURS nv1
106.4.4.7780.1  1% PROBA POUVOIR DU FROID nv1
110.2.4.0.1     HP +1%
110.3.4.0.1     MP +1%
			*/
		}
	}
}

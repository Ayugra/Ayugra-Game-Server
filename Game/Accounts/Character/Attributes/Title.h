#pragma once

/*
C : tit_eq [1:visible 2:effective] [conststring (9300 + title_id)]

S : title { title_id.status }
status :
	0/2/4/6 : non listé
	1 : listé non check
	3 : visible sous pseudo
	5 : coché effectif
	7 : visible sous pseudo et coché effectif
bit field
4 : effectif
2 : visible
1 : listé
4 2 1

titinfo [entity_type] [entity_id] [visible_title_constring] [effective_title_constring]

connexion :
title
titinfo

effet activation titre "joli" : eff_s [entity_type] [entity_id] [visual_effect (11)]

*/

class Title
{
public:
	Title(int VisibleTitleId = -1, int EffectiveTitleId = -1)
		: visibleTitleId(visibleTitleId)
		, effectiveTitleId(EffectiveTitleId)
	{

	}

	~Title()
	{

	}

private:
	int visibleTitleId;
	int effectiveTitleId;
};
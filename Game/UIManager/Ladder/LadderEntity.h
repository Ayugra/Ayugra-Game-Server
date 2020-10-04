#pragma once
#include <string>

/* Data can be :
* - Reputation
* - Compliment
* - Act4 points
*/
class LadderEntity
{
public:
    LadderEntity(int Data, int Level, int LevelH, std::string Pseudonym, int Id)
        : data(Data)
        , level(Level)
        , levelH(LevelH)
        , pseudonym(Pseudonym)
        , id(Id)
    {}

    int data;
    int level;
    int levelH;
    std::string pseudonym;
    int id;
};
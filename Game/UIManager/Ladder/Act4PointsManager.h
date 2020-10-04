#pragma once
#include <vector>
#include "Game/UIManager/Ladder/LadderEntity.h"
#include <iostream>

class Act4PointsManager
{
public:
    static int saveRecord(LadderEntity entity)
    {
        for (int i = 0; i < Act4pointsLadder.size(); i++)
            std::cout << "- " << Act4pointsLadder[i].data << std::endl;
        for (int i = 0; i < Act4pointsLadder.size(); i++)
        {
            if (Act4pointsLadder[i].id == entity.id)
            {
                Act4pointsLadder.erase(Act4pointsLadder.begin() + i);
                break;
            }
        }
        for (size_t i = 0; i < Act4pointsLadder.size(); i++)
        {
            if (entity.data > Act4pointsLadder[i].data && i < Act4pointsLadder.size() - 1)
                continue;
            if (Act4pointsLadder.size() > 42)
                Act4pointsLadder.erase(Act4pointsLadder.begin());
            if (entity.data > Act4pointsLadder[Act4pointsLadder.size() - 1].data)
            {
                Act4pointsLadder.insert(Act4pointsLadder.begin() + i + 1, entity);
                return (int)i + 1;
            }
            Act4pointsLadder.insert(Act4pointsLadder.begin() + i, entity);
            return (int)i;
        }
        if (Act4pointsLadder.size() == 0)
        {
            Act4pointsLadder.push_back(entity);
            return 0;
        }
        return -1;
    }

    static void setAct4pointsLadder(std::vector<LadderEntity> act4pointsValues)
    {
        Act4pointsLadder = act4pointsValues;
    }

    static std::vector<LadderEntity> getAct4pointsLadderEntities() { return Act4pointsLadder; }

private:
    static inline std::vector<LadderEntity> Act4pointsLadder;
};
#pragma once
#include <vector>
#include "Game/UIManager/Ladder/LadderEntity.h"
#include <iostream>

class ComplimentManager
{
public:
    static int saveRecord(LadderEntity entity)
    {
        for (int i = 0; i < ComplimentLadder.size(); i++)
            std::cout << "- " << ComplimentLadder[i].data << std::endl;
        for (int i = 0; i < ComplimentLadder.size(); i++)
        {
            if (ComplimentLadder[i].id == entity.id)
            {
                ComplimentLadder.erase(ComplimentLadder.begin() + i);
                break;
            }
        }
        for (size_t i = 0; i < ComplimentLadder.size(); i++)
        {
            if (entity.data > ComplimentLadder[i].data && i < ComplimentLadder.size() - 1)
                continue;
            if (ComplimentLadder.size() > 42)
                ComplimentLadder.erase(ComplimentLadder.begin());
            if (entity.data > ComplimentLadder[ComplimentLadder.size() - 1].data)
            {
                ComplimentLadder.insert(ComplimentLadder.begin() + i + 1, entity);
                return (int)i + 1;
            }
            ComplimentLadder.insert(ComplimentLadder.begin() + i, entity);
            return (int)i;
        }
        if (ComplimentLadder.size() == 0)
        {
            ComplimentLadder.push_back(entity);
            return 0;
        }
        return -1;
    }

    static void setComplimentLadder(std::vector<LadderEntity> complimentValues)
    {
        ComplimentLadder = complimentValues;
    }

    static std::vector<LadderEntity> getComplimentLadderEntities() { return ComplimentLadder; }

private:
    static inline std::vector<LadderEntity> ComplimentLadder;
};
#pragma once

#include <vector>
#include "Game/Types/ReputationType.h"
#include "Network/Packets/Server/UI/Ladder/S_flinit.h"
#include <iostream>

class ReputationManager
{
public:
    static int saveRecord(LadderEntity entity)
    {
        for (int i = 0; i < reputationLadder.size(); i++)
        {
            if (reputationLadder[i].id == entity.id)
            {
                reputationLadder.erase(reputationLadder.begin() + i);
                break;
            }
        }
        for (size_t i = 0; i < reputationLadder.size(); i++)
        {
            if (entity.data > reputationLadder[i].data && i < reputationLadder.size() - 1)
                continue;
            if (reputationLadder.size() > 42)
                reputationLadder.erase(reputationLadder.begin());
            if (entity.data > reputationLadder[reputationLadder.size() - 1].data)
            {
                reputationLadder.insert(reputationLadder.begin() + i + 1, entity);
                return (int)i + 1;
            }
            reputationLadder.insert(reputationLadder.begin() + i, entity);
            return (int)i;
        }
        if (reputationLadder.size() == 0)
        {
            reputationLadder.push_back(entity);
            return 0;
        }
        return -1;
    }

    static ReputationType getReputationType(LadderEntity entity)
    {
        int ladder = (int)reputationLadder.size() - saveRecord(entity);
        if (ladder == 1)
            return ReputationType::LEGENDARY_HERO;
        else if (ladder == 2)
            return ReputationType::MYSTERIOUS_HERO;
        else if (ladder == 3)
            return ReputationType::ANCIEN_HERO;
        else if (ladder >= 4 && ladder <= 13)
            return ReputationType::LEGEND_2;
        else if (ladder >= 14 && ladder <= 43)
            return ReputationType::LEGEND_1;
        if (entity.data <= 50)
            return ReputationType::BEGINNER_1;
        else if (entity.data <= 150)
            return ReputationType::BEGINNER_2;
        else if (entity.data <= 250)
            return ReputationType::BEGINNER_3;
        else if (entity.data <= 500)
            return ReputationType::TRAINEE_1;
        else if (entity.data <= 750)
            return ReputationType::TRAINEE_2;
        else if (entity.data <= 1000)
            return ReputationType::TRAINEE_3;
        else if (entity.data <= 2250)
            return ReputationType::EXPERIENCED_1;
        else if (entity.data <= 3500)
            return ReputationType::EXPERIENCED_2;
        else if (entity.data <= 5000)
            return ReputationType::EXPERIENCED_3;
        else if (entity.data <= 9500)
            return ReputationType::SOLDIER_1;
        else if (entity.data <= 19000)
            return ReputationType::SOLDIER_2;
        else if (entity.data <= 25000)
            return ReputationType::SOLDIER_3;
        else if (entity.data <= 40000)
            return ReputationType::EXPERT_1;
        else if (entity.data <= 60000)
            return ReputationType::EXPERT_2;
        else if (entity.data <= 85000)
            return ReputationType::EXPERT_3;
        else if (entity.data <= 115000)
            return ReputationType::LEADER_1;
        else if (entity.data <= 150000)
            return ReputationType::LEADER_2;
        else if (entity.data <= 190000)
            return ReputationType::LEADER_3;
        else if (entity.data <= 235000)
            return ReputationType::MASTER_1;
        else if (entity.data <= 285000)
            return ReputationType::MASTER_2;
        else if (entity.data <= 350000)
            return ReputationType::MASTER_3;
        else if (entity.data <= 500000)
            return ReputationType::NOS_1;
        else if (entity.data <= 1500000)
            return ReputationType::NOS_2;
        else if (entity.data <= 2500000)
            return ReputationType::NOS_3;
        else if (entity.data <= 3750000)
            return ReputationType::ELITE_1;
        else if (entity.data <= 5000000)
            return ReputationType::ELITE_2;
        return ReputationType::ELITE_3;
    }

    static void setReputationLadder(std::vector<LadderEntity> reputationValues)
    {
        reputationLadder = reputationValues;
    }

    static std::vector<LadderEntity> getReputationLadderEntities() { return reputationLadder; }

private:
    static inline std::vector<LadderEntity> reputationLadder;
};

#pragma once

enum class ReputationType
{
    BEGINNER_1 = 1, // (0 ~ 50 Reputation)
    BEGINNER_2 = 2, // (51 ~ 150 Reputation)
    BEGINNER_3 = 3, // (151 ~ 250 Reputation)

    TRAINEE_1 = 4, // (Reputation: 251 ~ 500)
    TRAINEE_2 = 5, // (Reputation:501 ~ 750)
    TRAINEE_3 = 6, // (Reputation: 751 ~ 1.000)

    EXPERIENCED_1 = 7, // (Reputation: 1.001 ~ 2.250)
    EXPERIENCED_2 = 8, // (Reputation: 2.251 ~ 3.500)
    EXPERIENCED_3 = 9, // (Reputation: 3.501 ~ 5.000)

    SOLDIER_1 = 10, // (Reputation: 5 001 ~ 9.500)
    SOLDIER_2 = 11, // (Reputation: 9.501 ~ 19.000)
    SOLDIER_3 = 12, // (Reputation: 19.001 ~ 25.000)

    EXPERT_1= 13, // (Reputation: 25.001 ~ 40.000)
    EXPERT_2 = 14, // (Reputation: 40.001 ~ 60.000)
    EXPERT_3 = 15, // (Reputation: 60.001 ~ 85.000)

    LEADER_1 = 16, // (Reputation: 85.001 ~ 115.000)
    LEADER_2 = 17, // (Reputation: 115.001 ~ 150.000)
    LEADER_3 = 18, // (Reputation: 150.001 ~ 190.000)

    MASTER_1 = 19, // (Reputation: 190.001 ~ 235.000)
    MASTER_2 = 20, // (Reputation: 235.001 ~ 285.000)
    MASTER_3 = 21, // (Reputation: 285.001 ~ 350.000)

    NOS_1 = 22, // (Reputation: 350.001 ~ 500.000)
    NOS_2 = 23, // (Reputation: 500.001 ~ 1.500.000)
    NOS_3 = 24, // (Reputation: 1.500.001 ~ 2.500.000)

    ELITE_1 = 25, // (Reputation: 2.500.001 ~ 3.750.000)
    ELITE_2 = 26, // (Reputation: 3.750.001 ~ 5.000.000)
    ELITE_3 = 27, // (Reputation: 5.000.001 and more )

    LEGEND_1 = 28, // (43th to 14th place at the reputation ranking : 5.000.000 and more)
    LEGEND_2 = 29, // (14th to 4th place at the reputation ranking : 5.000.000 and more)

    ANCIEN_HERO = 30, // (3rd place at the reputation ranking : 5.000.000 and more)
    MYSTERIOUS_HERO = 31, // (2nd place in the reputation ranking : 5.000.000 and more)
    LEGENDARY_HERO = 32 // (1st place in the reputation ranking : 5.000.000 and more)
};

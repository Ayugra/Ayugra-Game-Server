#pragma once

enum class ClassType
{
    ADVENTURER = 0,
    SWORDSMAN = 1,
    ARCHER = 2,
    MAGICIAN = 3,
    MARTIAL_ARTIST = 4
};

// Rework it
// Supposed to be a bit fields :
// MA M Ar S Ad All
// 16 8  4 2  1   0
enum class ClassCanHoldItemType
{
    ALL = 0,
    ADVENTURER = 1,
    SWORDSMAN = 2,
    ARCHER = 4,
    MAGICIAN = 8,
    ALL_EXCEPT_MA_ADV = 14,
    ALL_EXCEPT_MA = 15,
    MARTIAL_ARTIST = 16,
    ALL_EXCEPT_ADV = 30,
    ALL2 = 31 // HELLO ENTWELL ARE YOU OK ???
};
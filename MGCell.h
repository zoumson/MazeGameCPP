#pragma once
#include "MGUtility.h"
#include "MGPoint.h"

namespace za
{
    namespace mg
    {
        
        enum class MAZE_WAY
        {
            PATH = 0,

            ENTRANCE = 10,
            EXIT = 20,

            BONUS_10 = 30,
            BONUS_9,
            BONUS_8,
            BONUS_7,
            BONUS_6,
            BONUS_5,
            BONUS_4,
            BONUS_3,
            BONUS_2,
            BONUS_1,

            NORMAL = 40,

            ENEMY_15 = 50,
            ENEMY_14,
            ENEMY_13,
            ENEMY_12,
            ENEMY_11,
            ENEMY_10,
            ENEMY_9,
            ENEMY_8,
            ENEMY_7,
            ENEMY_6,
            ENEMY_5,
            ENEMY_4,
            ENEMY_3,
            ENEMY_2,
            ENEMY_1,

            WALL = 100,

        };
        
        struct Cell
        {

            MAZE_WAY val;
            bool visited;
            Cell(MAZE_WAY v = MAZE_WAY::WALL);
            Cell(const Cell& t);
            Cell(Cell&& t);
            Cell& operator=(const Cell& t);
            Cell& operator=(Cell&& t);

        };
    }
}



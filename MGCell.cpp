#include "MGCell.h"

namespace za
{
    namespace mg
    {

        Cell::Cell(MAZE_WAY v)
        {
            val = v;
            visited = false;
        }

        Cell::Cell(const Cell& t)
        {
            val = t.val;
            visited = t.visited;
        }
        Cell::Cell(Cell&& t)
        {
            val = t.val;
            visited = t.visited;

            t.val = MAZE_WAY::WALL;
            t.visited = false;
        }
        Cell& Cell::operator=(const Cell& t)
        {
            val = t.val;
            visited = t.visited;
            return *this;
        }
        Cell& Cell::operator=(Cell&& t)
        {
            val = t.val;
            visited = t.visited;

            t.val = MAZE_WAY::WALL;
            t.visited = false;
            return *this;
        }

    }
}


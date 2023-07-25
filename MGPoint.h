#pragma once
#include "MGUtility.h"


namespace za
{
    namespace mg
    {
        struct Point
        {
            int x, y;
            Point();
            Point(int _x, int _y);
            Point(const Point& t);
            Point(Point&& t);            
            
            Point& operator=(const Point& t);
            Point& operator=(Point&& t);

            bool operator>(const Point& pnt) const;
            bool operator== (Point const& pnt) const;
            //bool operator== (Point pnt);
            bool operator!= (Point const& pnt) const;

            bool friend operator< (const Point& lhs, const Point& rhs)
            {
                return !(lhs > rhs || lhs == rhs);
            }

            friend std::ostream& operator<<(std::ostream& os, const Point& pnt)
            {
                os << "(" << pnt.x << ", " << pnt.y << ")";

                return os;
            }

        };
    }
}
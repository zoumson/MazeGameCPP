#include "MGPoint.h"

namespace za
{
    namespace mg
    {
        Point::Point() :Point(0, 0) {};
        
        Point::Point(int _x, int _y) : x(_x), y(_y) {};
        
        Point::Point(const Point& t)
        {
            x = t.x;
            y = t.y;
        }
        
        Point::Point(Point&& t)
        {
            x = t.x;
            y = t.y;

            t.x = 0;
            t.y = 0;
        }
        
        Point& Point::operator=(const Point& t)
        {
            x = t.x;
            y = t.y;

            return *this;
        }
        
        Point& Point::operator=(Point&& t)
        {
            x = t.x;
            y = t.y;

            t.x = 0;
            t.y = 0;
            return *this;
        }
        
        bool Point::operator== (Point const & pnt) const
        {
            return x == pnt.x && y == pnt.y;
        }                       
        
        bool Point::operator!= (Point const& pnt) const
        {
            return this->x !=  pnt.x || this->y != pnt.y;
        }
        
        bool Point::operator>(const Point& pnt) const 
        {
            return (x > pnt.x) && (y > pnt.y);
        }
                
    }
}
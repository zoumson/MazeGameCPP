#pragma once
#include "MGPoint.h"
#include <utility>
#include <tuple>

//using namespace za::mg;

namespace za 
{
    namespace mg
    {
        namespace cmp
        {
            using p_p = std::pair<Point, Point>;
            using t_pd = std::tuple<Point, double>;
            using t_ppd = std::tuple<Point, Point, double>;

            struct comp_less_point
            {
                bool operator() (const Point& lhs, const Point& rhs) const;
            };

            struct comp_less_pair_point
            {
                bool operator() (const p_p& lhs, const p_p& rhs) const;
            };

            struct comp_less_tuple_point_double
            {

                bool operator() (const t_pd& lhs, const t_pd& rhs) const;
            };

            struct comp_greater_tuple_point_double
            {
                bool operator() (const t_pd& lhs, const t_pd& rhs) const;
            };

            struct comp_less_tuple_point_2_double
            {
                bool operator() (const t_ppd& lhs, const t_ppd& rhs) const;
            };

        }
    }
}


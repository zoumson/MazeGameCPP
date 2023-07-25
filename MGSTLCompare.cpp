#include "MGSTLCompare.h"

namespace za
{
    namespace mg
    {
        namespace cmp
        {

            bool comp_less_point::operator() (const Point& lhs, const Point& rhs) const
                {

                    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
                };

            bool comp_less_pair_point::operator() (const p_p& lhs, const p_p& rhs) const
            {
                return std::tie(lhs.first.x, lhs.first.y, lhs.second.x, lhs.second.y) <
                    std::tie(rhs.first.x, rhs.first.y, rhs.second.x, rhs.second.y);
            };

            bool comp_less_tuple_point_double::operator() (const t_pd& lhs, const t_pd& rhs) const
            {

                return std::tie(std::get<0>(lhs).x, std::get<0>(lhs).y, std::get<1>(lhs)) <
                    std::tie(std::get<0>(rhs).x, std::get<0>(rhs).y, std::get<1>(rhs));
            };

            bool comp_greater_tuple_point_double::operator() (const t_pd& lhs, const t_pd& rhs) const
            {
                return std::tie(std::get<0>(lhs).x, std::get<0>(lhs).y, std::get<1>(lhs)) >
                    std::tie(std::get<0>(rhs).x, std::get<0>(rhs).y, std::get<1>(rhs));
            };

            bool comp_less_tuple_point_2_double::operator() (const t_ppd& lhs, const t_ppd& rhs) const
            {

                return std::tie(std::get<0>(lhs).x, std::get<0>(lhs).y, std::get<1>(lhs).x, std::get<1>(lhs).y, std::get<2>(lhs)) <
                    std::tie(std::get<0>(rhs).x, std::get<0>(rhs).y, std::get<1>(lhs).x, std::get<1>(rhs).y, std::get<2>(rhs));
            };              
        }
    }
}

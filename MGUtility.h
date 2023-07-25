#pragma once
#include <tuple>
#include <ostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <set>
#include <iostream>
#include <map>
#include <unordered_map>
#include <numeric>
#include <ctype.h>
#include <cmath>
#include <limits>
#include <chrono>
#include <thread>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

namespace za
{
	namespace mg
	{

        template <typename Enumeration>
        auto as_integer(Enumeration const value)
            -> typename std::underlying_type<Enumeration>::type
        {
            return static_cast<typename std::underlying_type<Enumeration>::type>(value);
        }

	}
}
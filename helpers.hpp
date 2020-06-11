#pragma once
#include <algorithm>
#include <string>

namespace sis {
    class helpers {
    public:
        static std::string& str_to_lower(std::string& a_string) {
            std::transform(a_string.begin(), a_string.end(), a_string.begin(), tolower);
            return a_string;
        }
    };
}

#pragma once
#include <algorithm>
#include <string>
#include <sstream>

namespace sis {
    class helpers {
    public:
        static std::string& str_to_lower(std::string& a_string) {
            std::transform(a_string.begin(), a_string.end(), a_string.begin(), tolower);
            return a_string;
        }

        static std::vector<std::string> string_to_tokens(const std::string& a_string, const char delimiter = ' ') {
            std::vector<std::string> tokens;
            std::stringstream a_string_stream(a_string);
            std::string a_token;
            while (std::getline(a_string_stream, a_token, delimiter)) {
                tokens.push_back(a_token);
            }
            return tokens;
        }

        static std::string replace_char(const std::string& a_string, unsigned int index, const std::string&
                                        the_replacement) {
            auto replaced_string = a_string;
            replaced_string.replace(index, 1, the_replacement);
            return replaced_string;
        }
    };
}

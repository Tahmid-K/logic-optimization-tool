#include "pla_parser.hpp"

#include <iostream>

namespace sis {

    pla_parser::pla_parser(const std::string& a_file_path_string) : file_parser() {
        file_path_ = pla_parser::string_to_path(a_file_path_string);
    }

    bool pla_parser::parse() {
        if(open_file()) {
            std::string the_line;
            while(std::getline(a_stream_, the_line)){ 
                std::cout << the_line << "\n"; 
            }
            return true;
        }
        return false;
    }

    fs::path pla_parser::string_to_path(const std::string& a_file_path_string) {
        auto the_file_path = "./" + a_file_path_string;
        return fs::path(a_file_path_string);
    }
}

#pragma once
#include "file_parser.hpp"

namespace sis {
    class pla_parser :
        public file_parser {
    public:
        explicit pla_parser(const std::string& a_file_path_string);
        bool parse() override;
    protected:
        fs::path string_to_path(const std::string& a_file_path_string) override;

    };
}

#pragma once
#include "file_parser.hpp"

namespace sis {
    class pla_parser :
        public file_parser {
    public:
        explicit pla_parser(const std::string& a_file_path_string);
        bool parse(command_handler& a_command_handler) override;
    protected:
        fs::path string_to_path(const std::string& a_file_path_string) override;
        bool parse_pla_header(covers* the_covers);
        bool parse_pla_body(covers* the_covers);
        bool parse_literal(covers* the_covers);
        bool parse_end();

    };
}

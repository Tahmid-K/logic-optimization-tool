#include "pla_parser.hpp"

#include <iostream>

#include "covers.hpp"
#include "helpers.hpp"

namespace sis {

    pla_parser::pla_parser(const std::string& a_file_path_string) : file_parser() {
        file_path_ = pla_parser::string_to_path(a_file_path_string);
    }

    bool pla_parser::parse(command_handler& a_command_handler) {
        if(open_file()) {
            auto* the_covers = new covers();
            a_command_handler.set_covers(the_covers);
            if(parse_pla_header(the_covers)) {
                if(parse_pla_body(the_covers)) {
                    return true;
                }
            }
            delete the_covers;
        }
        return false;
    }

    fs::path pla_parser::string_to_path(const std::string& a_file_path_string) {
        auto the_file_path = "./" + a_file_path_string;
        return fs::path(a_file_path_string);
    }

    bool pla_parser::parse_pla_header(covers* the_covers) {
        const static auto header_size = 5;
        std::string the_line;
        for(auto i = 0; i < header_size-2; i++) {            
            if(!std::getline(a_stream_, the_line)) {
                return false;
            }
        }
        // 4th line containing the inputs
        if(std::getline(a_stream_, the_line)) {
            auto input_tokens = helpers::string_to_tokens(the_line);
            for(unsigned int i = 1; i < input_tokens.size(); i++) {
                the_covers->add_input_names(input_tokens[i]);
            }
            // 5th line containing the outputs
            if(std::getline(a_stream_, the_line)) {
                auto output_tokens = helpers::string_to_tokens(the_line);
                for(unsigned int i = 1; i < output_tokens.size(); i++) {
                    the_covers->add_function({output_tokens[i], implicants()});
                }
                return true;
            }
        }
        return false;
    }

    bool pla_parser::parse_pla_body(covers* the_covers) {
        std::string the_line;
        //5th line containing the number of literals
        if(std::getline(a_stream_,the_line)) {
            auto number_token = helpers::string_to_tokens(the_line);
            if(number_token.size() >= 2) {
                const auto number_of_literals = std::stoi(number_token[1]);
                for(auto i = 0; i < number_of_literals; i++) {
                    if(!parse_literal(the_covers)) {
                        return false;
                    }
                }
                return parse_end();
            }
        }
        return false;
    }

    bool pla_parser::parse_literal(covers* the_covers) {
        std::string the_line;
        if(std::getline(a_stream_, the_line)) {
            
        }
        return false;
    }

    bool pla_parser::parse_end() {
        std::string the_line;
        return static_cast<bool>(std::getline(a_stream_, the_line)) && the_line == ".e";
    }
}

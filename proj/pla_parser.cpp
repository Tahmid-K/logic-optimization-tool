#include "pla_parser.hpp"

#include <iostream>

#include "covers.hpp"
#include "helpers.hpp"

namespace sis {

    pla_parser::pla_parser(const std::string& a_file_path_string) : file_parser() {
        file_path_ = pla_parser::string_to_path(a_file_path_string);
    }

    bool pla_parser::parse(command_handler& a_command_handler) {
        if (open_file()) {
            auto* the_covers = new covers();
            if (parse_pla_header(the_covers)) {
                if (parse_pla_body(the_covers)) {
                    if (parse_end()) {
                        a_command_handler.set_covers(the_covers);
                        return true;
                    }
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
        for (auto i = 0; i < header_size - 3; i++) {
            if (!std::getline(a_stream_, the_line)) {

                return false;
            }
            // temp solution to type in some headers
            if (the_line == ".type fd") {
                if (!std::getline(a_stream_, the_line)) {
                    return false;
                }
            }
        }
        // 4th line containing the inputs
        if (std::getline(a_stream_, the_line)) {
            auto input_tokens = helpers::string_to_tokens(the_line);
            for (unsigned int i = 1; i < input_tokens.size(); i++) {
                the_covers->add_input_names(input_tokens[i]);
            }
            // 5th line containing the outputs
            if (std::getline(a_stream_, the_line)) {
                auto output_tokens = helpers::string_to_tokens(the_line);
                for (unsigned int i = 1; i < output_tokens.size(); i++) {
                    the_covers->add_output_names(output_tokens[i]);
                    the_covers->get_on_sets().emplace_back();
                    the_covers->get_dc_sets().emplace_back();
                }
                return true;
            }
        }
        return false;
    }

    bool pla_parser::parse_pla_body(covers* the_covers) {
        std::string the_line;
        //5th line containing the number of literals
        if (std::getline(a_stream_, the_line)) {
            auto number_token = helpers::string_to_tokens(the_line);
            if (number_token.size() >= 2) {
                const auto number_of_literals = std::stoi(number_token[1]);
                for (auto i = 0; i < number_of_literals; i++) {
                    if (!parse_literal(the_covers)) {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool pla_parser::parse_literal(covers* the_covers) {
        std::string the_line;
        if (std::getline(a_stream_, the_line)) {
            auto implicant_token = helpers::string_to_tokens(the_line);
            if (validate_implicant(the_covers, implicant_token)) {
                const auto the_implicant = implicant_token[0];
                const auto the_outputs = implicant_token[1];
                for (unsigned int i = 0; i < the_outputs.size(); i++) {
                    if (the_outputs[i] == '1') {
                        the_covers->add_on_set(the_implicant, i);
                    }
                    else if (the_outputs[i] == '-' || the_outputs[i] == '2') {
                        the_covers->add_dc_set(the_implicant, i);
                    }
                }
                return true;
            }
        }
        return false;
    }

    bool pla_parser::parse_end() {
        std::string the_line;
        return static_cast<bool>(std::getline(a_stream_, the_line)) && (the_line == ".e" || the_line == ".end");
    }

    bool pla_parser::validate_implicant(covers* the_covers, const std::vector<std::string>& a_literal) {
        // literal should be the same size as the inputs and the the number of outputs should be the same as the number of functions
        if (a_literal.size() == 2) {
            if (a_literal[0].size() == the_covers->get_input_names().size()) {
                if (a_literal[1].size() == the_covers->get_output_names().size()) {
                    return true;
                }
            }
        }
        return false;
    }
}

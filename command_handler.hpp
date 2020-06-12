#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "command.hpp"
#include "covers.hpp"

namespace sis {
    class command_handler {
    public:
        explicit command_handler();
        ~command_handler();
        command_handler(command_handler& the_copy) = default;
        command_handler& operator=(const command_handler& the_other) = default;
        command* handle(std::string the_user_input);
        void set_covers(covers* the_covers) {the_covers_ = the_covers;}
    protected:
        command* create_help_command();
        command* create_espresso_command();
        command* create_read_pla_command();
        command* create_write_eqn_command();

        std::string current_token() {return tokens_[current_index_];}
        void next_token() {current_index_++;}
        [[nodiscard]] bool has_remaining() const {return current_index_ < tokens_.size();}
        std::vector<std::string> tokens_;
        covers* the_covers_;
        uint32_t current_index_;
    };
}

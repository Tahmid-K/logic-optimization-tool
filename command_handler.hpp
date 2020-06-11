#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "command.hpp"

namespace sis {
    class command_handler {
    public:
        command_handler( std::istream& a_stream);
        ~command_handler() = default;
        command_handler(command_handler& the_copy) = default;
        command_handler& operator=(const command_handler& the_other) = default;

        command* handle(std::ostream& a_stream);
    protected:     
        command* create_help_command();
        command* create_expresso_statement();
        std::string current_token() {return tokens_[current_index_];}
        void next_token() {current_index_++;}
        bool has_remaining() const {return current_index_ < tokens_.size();}
        std::vector<std::string> tokens_;
        uint32_t current_index_;
    };
}

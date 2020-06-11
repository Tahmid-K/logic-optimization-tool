#include "command_handler.hpp"

#include <map>
#include <unordered_map>

#include "optimization_commands.hpp"
#include "print_commands.hpp"
#include "read_commands.hpp"


namespace sis {

    typedef command* (command_handler::*create_method)();
    typedef std::unordered_map<std::string, create_method> input_to_command_map;

    command_handler::command_handler(std::istream& a_stream) : current_index_(0) {
        std::string a_token;
        while (std::getline(a_stream, a_token, ' ')) {
            tokens_.push_back(a_token);
        }
    }

    command* command_handler::handle(std::ostream& a_stream) {
        static input_to_command_map the_map = {
            {"help", &command_handler::create_help_command},
            {"read_pla", &command_handler::create_read_pla_command},
            {"expresso", &command_handler::create_help_command}
        };
        if (the_map.contains(current_token())) {
           return (this->*the_map[current_token()])();
        }
        return nullptr;
    }

    command* command_handler::create_help_command() {
        next_token();
        return new help_command(command_type::help);
    }

    command* command_handler::create_expresso_command() {
        next_token();
        return new expresso_command(command_type::expresso);
    }

    command* command_handler::create_read_pla_command() {
        next_token();
        if(has_remaining()) {
            return new read_pla_command(current_token()); 
        }
        return nullptr;
    }

}

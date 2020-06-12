#include "command_handler.hpp"

#include <map>
#include <unordered_map>


#include "helpers.hpp"
#include "optimization_commands.hpp"
#include "print_commands.hpp"
#include "read_commands.hpp"


namespace sis {

    typedef command* (command_handler::*create_method)();
    typedef std::unordered_map<std::string, create_method> input_to_command_map;

    command_handler::command_handler() : the_covers_(nullptr), current_index_(0) {
    }

    command_handler::~command_handler() {
        delete the_covers_;
    }

    command* command_handler::handle(std::string the_user_input) {
        static input_to_command_map the_map = {
            {"help", &command_handler::create_help_command},
            {"read_pla", &command_handler::create_read_pla_command},
            {"espresso", &command_handler::create_espresso_command},
            {"write_eqn", &command_handler::create_write_eqn_command}
        };
        current_index_ = 0;
        tokens_ = helpers::string_to_tokens(the_user_input);
        if (the_map.contains(current_token())) {
           return (this->*the_map[current_token()])();
        }
        return nullptr;
    }

    command* command_handler::create_help_command() {
        next_token();        
        return new help_command();
    }

    command* command_handler::create_read_pla_command() {
        next_token();
        if(has_remaining()) {
            return new read_pla_command(this,current_token()); 
        }
        return nullptr;
    }

    command* command_handler::create_espresso_command() {
        next_token();       
        if(the_covers_ != nullptr) {
            return new espresso_command(the_covers_);
        }
        return nullptr;
    }

    command* command_handler::create_write_eqn_command() {
        next_token();
        if(the_covers_ != nullptr) {
            return new write_eqn_command(the_covers_);
        }
        return nullptr;
    }

}

#include "command_handler.hpp"

#include <map>
#include <unordered_map>



#include "espresso.hpp"
#include "helpers.hpp"
#include "print.hpp"
#include "read.hpp"


namespace sis {

    typedef command* (command_handler::*create_method)();
    typedef std::unordered_map<std::string, create_method> input_to_command_map;

    command_handler::command_handler() : the_covers_(nullptr), the_timer_(nullptr), current_index_(0) {
    }

    command_handler::~command_handler() {
        delete the_covers_;
        delete the_timer_;
    }

    command* command_handler::handle(const std::string& the_user_input) {
        static input_to_command_map the_map = {
            {"help", &command_handler::create_help_command},
            {"read_pla", &command_handler::create_read_pla_command},
            {"espresso", &command_handler::create_espresso_command},
            {"write_eqn", &command_handler::create_write_eqn_command},
            {"time", &command_handler::create_time_command},
            {"print_stats", &command_handler::create_print_stats_command}
        };
        current_index_ = 0;
        tokens_ = helpers::string_to_tokens(the_user_input);
        if (the_map.contains(current_token())) {
           return (this->*the_map[current_token()])();
        }
        return nullptr;
    }

    void command_handler::start_timer() {
        if(the_timer_ != nullptr) {
            the_timer_->start();
        }       
    }

    void command_handler::end_timer(std::ostream& a_stream) {
        if(the_timer_ != nullptr) {
            the_timer_->stop();            
            // temp solution to skip timing the immediate command
            if(!the_timer_->get_skip()) {
                a_stream << "Command took " << the_timer_->get_duration() << std::endl;
                delete the_timer_;
                the_timer_ = nullptr;    
            }
            else {
                the_timer_->set_skip(false);   
            }           
        }
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

    command* command_handler::create_time_command() {
        next_token(); 
        the_timer_ = new timer();
        return new time_command();             
    }

    command* command_handler::create_print_stats_command() {
        next_token();
        if(the_covers_ != nullptr) {
            return new print_stats_command(the_covers_);
        }
        return nullptr;
    }

}

#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "command.hpp"
#include "covers.hpp"
#include "timer.hpp"

namespace sis {
    class command_handler {
    public:
        explicit command_handler();
        ~command_handler();
        command_handler(command_handler& the_copy) = default;
        command_handler& operator=(const command_handler& the_other) = default;
        command* handle(const std::string& the_user_input);
        [[nodiscard]] timer* get_timer() const {return the_timer_;}
        void set_timer(timer* a_timer) {the_timer_ = a_timer;}
        void set_covers(covers* the_covers) {the_covers_ = the_covers;}
        void start_timer();
        void end_timer(std::ostream& a_stream);
    protected:
        command* create_help_command();
        command* create_espresso_command();
        command* create_read_pla_command();
        command* create_write_eqn_command();
        command* create_time_command();
        command* create_print_stats_command();

        std::string current_token() {return tokens_[current_index_];}
        void next_token() {current_index_++;}
        [[nodiscard]] bool has_remaining() const {return current_index_ < tokens_.size();}
        std::vector<std::string> tokens_;
        covers* the_covers_;
        timer* the_timer_;
        uint32_t current_index_;
    };
}

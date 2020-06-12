#pragma once
#include <string>

#include "command.hpp"
#include "command_handler.hpp"

namespace sis {
    class read_command :
        public command {
    public:
        read_command(command_type a_command_type, command_handler* a_command_handler, std::string a_file_name);
    protected:
        command_handler* a_command_handler_;
        std::string file_name_;
        bool parse_error_;
    };

    class read_pla_command :
        public read_command {
    public:
        explicit read_pla_command(command_handler* a_command_handler, std::string a_file_name);
        void execute() override;
        void display(std::ostream& a_stream) override;
        
    };
}

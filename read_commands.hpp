#pragma once
#include <string>

#include "command.hpp"

namespace sis {
    class read_command :
        public command {
    public:
        read_command(command_type a_command_type, std::string a_file_name);
    protected:
        std::string file_name_;
    };

    class read_pla_command :
        public read_command {
    public:
        explicit read_pla_command(std::string a_file_name);
        void execute() override;
        void display(std::ostream& a_stream) override;
        
    };
}
